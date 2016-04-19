#ifndef _MOTOR_H
#define _MOTOR_H

#include <stdint.h>

#ifndef MATLAB_MEX_FILE

#include "Actuators.h"

#endif

//void Motor_Initialization();

uint16_t Motor_Set (uint8_t cmd[]);

#endif
