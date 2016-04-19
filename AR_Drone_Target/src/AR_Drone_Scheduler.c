/* Arduino Bareboard scheduler
 *
 * Copyright 2013 The MathWorks, Inc.
 */

//#include "AR_Drone_Scheduler.h"


#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "rtwtypes.h"

#define BaseRateTimer_NUM 1 //we'll only have one base rate timer in our model, all subrates derived from this

//extern void rt_OneStep(void);
void model_step(uint8_t timerID);
int SysTime (float modelBaseRate);
uint32_t ticksOfSec (float seconds);
typedef void (*SysTimeCB) (uint8_t id);
typedef uint8_t tid_t ; //for timer ID stuff
int registerTimer (float duration, SysTimeCB cb);
void sysTickHandler (int signum);

struct Timer {
        int          inUse ; //USED TO BE A BOOL
        SysTimeCB     cb;
        volatile int elapsed;  //USED TO BE A BOOL
        uint32_t        endTime ; ///< in SYS_TIME_TICKS
        uint32_t        duration; ///< in SYS_TIME_TICKS
};
    
volatile uint32_t nbSec;       ///< full seconds since startup
volatile uint32_t nbSecRem;   ///< remainder of seconds since startup in CPU_TICKS
volatile uint32_t nbTicks;      ///< SYS_TIME_TICKS since startup

struct Timer timer[BaseRateTimer_NUM];

float resolution;               ///< sys_time_timer resolution in seconds
uint32_t ticksPerSec;         ///< sys_time ticks per second (SYS_TIME_FREQUENCY)
uint32_t resolutionCPUTicks;  ///< sys_time_timer resolution in cpu ticks
uint32_t cpuTicksPerSec;     ///< cpu ticks per second


	
int m_systime = 0; //used to init timer





int getSysTime(float modelBaseRate){
if (m_systime == 0) {
        m_systime = SysTime (modelBaseRate) ; //after timer has been init, set to 1
    }
    return m_systime ;
}

void configureTimer(float modelBaseRate)
{int i = 0;
int setup;
   setup = getSysTime(modelBaseRate);
   i = registerTimer (modelBaseRate, model_step);
}

void model_step(uint8_t timerID)
{
  rt_OneStep();
 // printf("got inside model_step /n");
  /* Get model outputs here */
}

void sysTickHandler (int signum) {
  unsigned int i;
  nbTicks++;
 // printf("Inside sysTickHandler, current tick count: %d \n", nbTicks);
  nbSecRem += resolutionCPUTicks;;
    if (nbSecRem >= cpuTicksPerSec) {
        nbSecRem -= cpuTicksPerSec;
        nbSec++;
    }
   
    for (i=0; i < BaseRateTimer_NUM; i++) {
        if (timer[i].inUse &&  nbTicks >= timer[i].endTime) {
            timer[i].endTime += timer[i].duration;
            timer[i].elapsed = 1; //true
            if (timer[i].cb) {
                timer[i].cb(i);
            }
        }
    }
   
}

int SysTime (float modelBaseRate) {
    
    //declare
	float SYS_TIME_FREQUENCY = 1/modelBaseRate;
    struct sigaction sa;
    struct itimerval interval_timer;

    //initialize
    nbSec     = 0;
    nbSecRem = 0;
    nbTicks    = 0;

    ticksPerSec = SYS_TIME_FREQUENCY;
    resolution = 1.0 / ticksPerSec;
//     resolution = 1.0;
	unsigned int i;
    for (i=0; i<BaseRateTimer_NUM; i++) {  //only need one timer: the base rate one
        timer[i].inUse     = false;
        timer[i].cb         = NULL;
        timer[i].elapsed    = false;
        timer[i].endTime   = 0;
        timer[i].duration   = 0;
    }

    cpuTicksPerSec = 1e6;
    resolutionCPUTicks = (uint32_t)(resolution * cpuTicksPerSec + 0.5);

   

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &sysTickHandler;
    sigaction(SIGALRM, &sa, 0);

    // timer expires after this->resolution sec
    interval_timer.it_value.tv_sec = 0;
    interval_timer.it_value.tv_usec = resolution * 1e6 ;
    // and every SYS_TIME_RESOLUTION sec after that
    interval_timer.it_interval.tv_sec = 0;
    interval_timer.it_interval.tv_usec = resolution * 1e6 ;

    setitimer(ITIMER_REAL, &interval_timer, 0);
    
 return 1;   
}


int registerTimer (float duration, SysTimeCB cb) {
    uint32_t start_time = nbTicks;
    int i;
    for (i = 0; i< BaseRateTimer_NUM; i++) {
        if (!timer[i].inUse) {
            timer[i].cb         = cb;
            timer[i].elapsed    = 0;
            timer[i].endTime   = start_time + ticksOfSec (duration);
            timer[i].duration   = ticksOfSec (duration);
            timer[i].inUse     = 1;
            return i;
        }
    }
    return -1;
}


int checkAndAckTimer (tid_t id) {
    if (timer[id].elapsed) {
        timer[id].elapsed = 0;
        return 1;
    }
    return 0;
}

 uint32_t ticksOfSec (float seconds) {
        return (uint32_t)(seconds * ticksPerSec + 0.5);
    }
