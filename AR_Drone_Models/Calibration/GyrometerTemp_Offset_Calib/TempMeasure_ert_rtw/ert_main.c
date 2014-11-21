/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'TempMeasure'.
 *
 * Model version                  : 1.88
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Tue Jul 29 12:58:50 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stdio.h>
#include <stdlib.h>
#include "TempMeasure.h"
#include "TempMeasure_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "linuxinitialize.h"

sem_t stopSem;
sem_t termSem;
sem_t baserateTaskSem;
sem_t subrateTaskSem[2];
int taskId[2];
pthread_t terminateThread;
pthread_t schedulerThread;
pthread_t baseRateThread;
pthread_t subRateThread[2];
int subratePriority[2];
void subrateTask(void *arg)
{
  int tid = *((int *) arg);
  int subRateId;
  subRateId = tid + 1;
  while (1) {
    sem_wait(&subrateTaskSem[tid]);

#ifdef MW_RTOS_DEBUG

    printf(" -subrate task %d semaphore received\n", subRateId);

#endif

    switch (subRateId) {
     case 1:
      TempMeasure_step1();

      /* Get model outputs here */
      break;

     case 2:
      TempMeasure_step2();

      /* Get model outputs here */
      break;

     default:
      break;
    }
  }
}

void baseRateTask(void *arg)
{
  volatile boolean_T noErr;
  int_T i;
  TempMeasure_initialize();

  /* External mode */
  rtSetTFinalForExtMode(&rtmGetTFinal(TempMeasure_M));
  rtExtModeCheckInit(3);

  {
    boolean_T rtmStopReq = false;
    rtExtModeWaitForStartPkt(TempMeasure_M->extModeInfo, 3, &rtmStopReq);
    if (rtmStopReq) {
      rtmSetStopRequested(TempMeasure_M, true);
    }
  }

  rtERTExtModeStartMsg();
  noErr = (rtmGetErrorStatus(TempMeasure_M) == (NULL)) && !rtmGetStopRequested
    (TempMeasure_M);
  while (noErr ) {
    sem_wait(&baserateTaskSem);

#ifdef MW_RTOS_DEBUG

    printf("*base rate task semaphore received\n");
    fflush(stdout);

#endif

    for (i = 1
         ; i <= 2; i++) {
      if (rtmStepTask(TempMeasure_M, i)
          ) {
        sem_post(&subrateTaskSem[ i - 1
                 ]);
      }
    }

    /* External mode */
    {
      boolean_T rtmStopReq = false;
      rtExtModePauseIfNeeded(TempMeasure_M->extModeInfo, 3, &rtmStopReq);
      if (rtmStopReq) {
        rtmSetStopRequested(TempMeasure_M, true);
      }

      if (rtmGetStopRequested(TempMeasure_M) == true) {
        rtmSetErrorStatus(TempMeasure_M, "Simulation finished");
        break;
      }
    }

    /* External mode */
    {
      boolean_T rtmStopReq = false;
      rtExtModeOneStep(TempMeasure_M->extModeInfo, 3, &rtmStopReq);
      if (rtmStopReq) {
        rtmSetStopRequested(TempMeasure_M, true);
      }
    }

    TempMeasure_step0();

    /* Get model outputs here */
    rtExtModeCheckEndTrigger();
    noErr = (rtmGetErrorStatus(TempMeasure_M) == (NULL)) && !rtmGetStopRequested
      (TempMeasure_M);
  }

  sem_post(&termSem);
}

void exitTask(void *arg)
{
  sem_post(&stopSem);
}

void terminateTask(void *arg)
{
  sem_wait(&termSem);
  printf("**terminating the model**\n");
  fflush(stdout);
  rtExtModeShutdown(3);

  /* Disable rt_OneStep() here */

  /* Terminate model */
  TempMeasure_terminate();
  sem_post(&stopSem);
}

int main(int argc, char **argv)
{
  subratePriority[0] = 40;
  subratePriority[1] = 39;
  printf("**starting the model**\n");
  fflush(stdout);
  rtmSetErrorStatus(TempMeasure_M, 0);
  rtExtModeParseArgs(argc, (const char_T **)argv, NULL);

  /* Call RTOS Initialization funcation */
  myRTOSInit(0.0025, 2);

  /* Wait for stop semaphore */
  sem_wait(&stopSem);
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
