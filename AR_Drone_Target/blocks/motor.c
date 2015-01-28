#include "motor.h"

uint16_t Motor_Set (uint8_t cmd[])
{
#ifndef MATLAB_MEX_FILE
 uint16_t gpio_pin;
    gpio_pin = setPWM(cmd);

#endif
}
