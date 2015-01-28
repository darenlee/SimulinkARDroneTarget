#ifndef _LED_H
#define _LED_H

#include<stdint.h>

#ifndef MATLAB_MEX_FILE
#include "Actuators.h"
#endif

//void LED_Initialization ();
void LED_set(uint8_t cmd[]);
//void LED_stop();
#endif