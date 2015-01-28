/* Copyright 2013 The MathWorks, Inc. */


/* ---------------------------- */
/* RTOS-specific headers        */
/* Note: must be included first */
/* ---------------------------- */
#include "linuxinitialize.h"

/* ---------------------------- */
/* Required Coder Target header */
/* ---------------------------- */
#include "MW_custom_RTOS_header.h"

/* ---------------------------- */
/* RTOS-specific declarations   */
/* ---------------------------- */
pthread_attr_t attr;
baseRateInfo_t info;
struct sched_param sp;

#define CHECK_STATUS(status, expStatus, fcn) if (status != expStatus) {fprintf(stderr, "Call to %s returned error status (%d).\n", fcn, status); perror(fcn); fflush(stderr); exit(EXIT_FAILURE);}
#define CHECK_STATUS_NOT(status, errStatus, fcn) if (status == errStatus) {fprintf(stderr, "Call to %s returned error status (%d).\n", fcn, status); perror(fcn); fflush(stderr); exit(EXIT_FAILURE);}

/* ---------------------------- */
/* Internally visible functions */
/* ---------------------------- */
void setTaskPeriod(double periodInSeconds, int sigNo)
{
  timer_t timerId;
  struct sigevent sev;
  struct itimerspec its;
  long stNanoSec;
  int status;

  /* Create a timer */
  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = sigNo;
  sev.sigev_value.sival_ptr = &timerId;
  status = timer_create(CLOCK_REALTIME, &sev, &timerId);
  CHECK_STATUS(status, 0,"timer_create");

  /* Arm real-time scheduling timer */
  stNanoSec = (long)(periodInSeconds * 1e9);
  its.it_value.tv_sec = stNanoSec / 1000000000;
  its.it_value.tv_nsec = stNanoSec % 1000000000;
  its.it_interval.tv_sec = its.it_value.tv_sec;
  its.it_interval.tv_nsec = its.it_value.tv_nsec;
  status = timer_settime(timerId, 0, &its, NULL);
  CHECK_STATUS(status, 0,"timer_settime");
}

void schedulerTask(void* arg)
{
    baseRateInfo_t info = *((baseRateInfo_t *)arg);
#ifdef MW_RTOS_DEBUG
	printf("schedulerTask entered\n");
    fflush(stdout);
#endif
    setTaskPeriod(info.period, info.sigNo);    
    while(1) {
		myWaitForThisEvent(info.sigNo);
        sem_post(&baserateTaskSem);    
    }
}

/* Should use this fcn, but currently are not using it */
/* Why: it is safe ??? from interruption */
void my_sem_wait(sem_t *sem)
{
  int status;
  while (((status = sem_wait(sem)) == -1) && (errno == EINTR)) {
    /* Restart if interrupted by a signal */
    continue;
  }
  CHECK_STATUS(status, 0, "my_sem_wait");
}

/* ---------------------------- */
/* Externally visible functions */
/* ---------------------------- */
void myWaitForThisEvent(int sigNo)
{
	int status;
    sigset_t sigMask;

    sigemptyset(&sigMask);
    sigaddset(&sigMask, sigNo);
	status = sigwaitinfo(&sigMask, NULL);
	CHECK_STATUS_NOT(status, -1, "sigwaitinfo");
}

void myAddBlockForThisEvent(int sigNo)
{
	int status;
    sigset_t sigMask;

    sigemptyset(&sigMask);
    sigaddset(&sigMask, sigNo);
    status = pthread_sigmask(SIG_BLOCK, &sigMask, NULL);
    CHECK_STATUS(status, 0, "pthread_sigmask");
}

void myAddHandlerForThisEvent(int sigNo, int sigToBlock[], int numSigToBlock, void *sigHandler)
{
	int idx;
    int status;
    struct sigaction sa;

    sa.sa_handler = sigHandler;
    sigemptyset(&sa.sa_mask);
	for (idx=0; idx<numSigToBlock; idx++) 
	{
		sigaddset(&sa.sa_mask, sigToBlock[idx]);
	}
    sa.sa_flags = SA_RESTART; /* Restart functions if interrupted by handler */
	status = sigaction(sigNo, &sa, NULL);
    CHECK_STATUS_NOT(status, -1, "sigaction to register a signal handler");
}

void myRestoreDefaultHandlerForThisEvent(int sigNo)
{
	int status;
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; /* Restart functions if interrupted by handler */
    status = sigaction(sigNo, &sa, NULL);
	CHECK_STATUS_NOT(status, -1, "sigaction to restore default signal handler");
}

void myRTOSInit(double baseRatePeriod, int numSubrates)
{
	int i;
	int status;
	uid_t euid;
	size_t stackSize;
	unsigned long cpuMask = 0x1;
	unsigned int len = sizeof(cpuMask);

    if (!MW_IS_CONCURRENT)
	{
		/* All threads created by this process will run on a single CPU */
		status = sched_setaffinity(0, len, (cpu_set_t *) &cpuMask);
		CHECK_STATUS(status, 0,"sched_setaffinity");
	}

	status = sem_init(&termSem, 0, 0);
	CHECK_STATUS(status, 0,"sem_init:termSem");

#if !defined (_POSIX_THREAD_PRIORITY_SCHEDULING)
	fprintf(stderr, "Priority scheduling is NOT supported by your system.\n");
	fprintf(stderr, "The generated code will not run correctly because your\n");
	fprintf(stderr, "model contains multiple rates and uses multi-tasking\n");
	fprintf(stderr, "code generation mode. You can only run the generated code\n");
	fprintf(stderr, "in single-tasking mode in your system. Open\n");
	fprintf(stderr, "Simulation -> Configuration Parameters -> Solver dialog\n");
	fprintf(stderr, "and set \"Tasking mode for periodic sample times\" parameter to SingleTasking.\n");
	fprintf(stderr, "Re-build the Simulink model with the new settings and try executing the generated code again.\n");
	fflush(stderr);
	exit(EXIT_FAILURE);
#endif

	/* Need root privileges for real-time scheduling */
	euid = geteuid();
	if (euid != 0) {
	    fprintf(stderr, "You must have root privileges to run the generated code because\n");
	    fprintf(stderr, "generated code requires SCHED_FIFO scheduling class to run correctly.\n");
	    fprintf(stderr, "Try running the executable with the following command: sudo ./<executable name>\n");
	    fflush(stderr);
	    exit(EXIT_FAILURE);
	}

	/* Set scheduling policy of the main thread to SCHED_FIFO */
	sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
	status = sched_setscheduler(0, SCHED_FIFO, &sp);
	CHECK_STATUS(status, 0,"sched_setscheduler");

	/* Create threads executing the Simulink model */
	pthread_attr_init(&attr);
	status = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	CHECK_STATUS(status, 0,"pthread_attr_setinheritsched");
	status = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	CHECK_STATUS(status, 0,"pthread_attr_setschedpolicy");
	status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	CHECK_STATUS(status, 0,"pthread_attr_setdetachstate");

	/* PTHREAD_STACK_MIN is the minimum stack size required to start a thread */
	stackSize = 64 + PTHREAD_STACK_MIN;
	status = pthread_attr_setstacksize(&attr, stackSize);
	CHECK_STATUS(status, 0,"pthread_attr_setstacksize");

	/* Block signal used for timer notification */
	info.period = MW_BASERATE_PERIOD;
	info.sigNo = SIGRTMIN;
	sigemptyset(&info.sigMask);

    sigaddset(&info.sigMask, info.sigNo);
	myAddBlockForThisEvent(info.sigNo);

	signal(SIGTERM, exitTask);     /* kill */
	signal(SIGHUP, exitTask);      /* kill -HUP */
	signal(SIGINT, exitTask);      /* Interrupt from keyboard */
	signal(SIGQUIT, exitTask);     /* Quit from keyboard */

#ifdef MW_HAS_MULTIPLE_RATES
#ifdef MW_RTOS_DEBUG    
	printf("**creating subrate task threads**\n");
    fflush(stdout);
#endif    
	for (i = 0; i < MW_NUMBER_SUBRATES; i++) {
		taskId[i] = i;
		status = sem_init(&subrateTaskSem[i], 0, 0);
		CHECK_STATUS(status, 0,"sem_init");
		sp.sched_priority = MW_BASERATE_PRIORITY -40 + subratePriority[i] - 1;
		status = pthread_attr_setschedparam(&attr, &sp);
		CHECK_STATUS(status, 0,"pthread_attr_setschedparam");
		status = pthread_create(&subRateThread[i], &attr, (void *) subrateTask, (void *)&taskId[i]);
		CHECK_STATUS(status, 0,"pthread_create");
#ifdef COREAFFINITYREQUIRED
        if (coreAffinity[i] >= 0) {
 	        cpu_set_t cpuset;
 	        CPU_ZERO(&cpuset);
 	        CPU_SET(coreAffinity[i], &cpuset);
 	        ret = pthread_setaffinity_np(subRateThread[i], sizeof(cpu_set_t), &cpuset);
 	        CHECK_STATUS(ret, "pthread_setaffinity_np");
 	    }
#endif
	}
#endif

#ifdef MW_RTOS_DEBUG
	printf("**creating the base rate task thread**\n");
    fflush(stdout);
#endif    
	sp.sched_priority = MW_BASERATE_PRIORITY;
	status = pthread_attr_setschedparam(&attr, &sp);
	CHECK_STATUS(status, 0,"pthread_attr_setschedparam");
	status = pthread_create(&baseRateThread, &attr, (void *) baseRateTask, (void *) &info);
	CHECK_STATUS(status, 0,"pthread_create");

#ifdef MW_RTOS_DEBUG
	printf("**creating the terminate thread**\n");
    fflush(stdout);
#endif    
	sp.sched_priority = MW_BASERATE_PRIORITY;
	status = pthread_attr_setschedparam(&attr, &sp);
	CHECK_STATUS(status, 0,"pthread_attr_setschedparam");
	status = pthread_create(&terminateThread, &attr, (void *) terminateTask, (void *) &info);
	CHECK_STATUS(status, 0,"pthread_create");

#ifdef MW_RTOS_DEBUG
	printf("**creating the scheduler thread**\n");
    fflush(stdout);
#endif    
	sp.sched_priority = MW_BASERATE_PRIORITY;
	status = pthread_attr_setschedparam(&attr, &sp);
	CHECK_STATUS(status, 0,"pthread_attr_setschedparam");
	status = pthread_create(&schedulerThread, &attr, (void *) schedulerTask, (void *) &info);
	CHECK_STATUS(status, 0,"pthread_create");

#ifdef MW_HAS_APERIODIC_TASKS
#ifdef MW_RTOS_DEBUG    
	printf("**creating asynchronously triggered task threads**\n");
    fflush(stdout);
#endif    
	sp.sched_priority = MW_BASERATE_PRIORITY - 1;
	for (i = 0; i < MW_NUMBER_APERIODIC_TASKS; i++) {
		status = pthread_create(&asyncThread[i], &attr, (void *) pAsyncTasks[i], NULL);
		CHECK_STATUS(status, 0,"pthread_create");
	}
#endif

	pthread_attr_destroy(&attr);
	fflush(stdout);
}