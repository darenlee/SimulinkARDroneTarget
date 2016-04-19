/* AR Drone Bareboard scheduler
 * 
 * Copyright 2013 The MathWorks, Inc.
 */

#ifndef _ARDRONESCHEDULER_H_
#define _ARDRONESCHEDULER_H_


#include <sys/time.h>
#include <signal.h>
#include <string.h>	
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// #include "rtwtypes.h"



extern void rt_OneStep(void);
extern void configureTimer(float modelBaseRate);



#endif // _ARDUINOSCHEDULER_H_
