#include "led.h"
#include <signal.h>
/*void LED_Initialization ()
{
#ifndef MATLAB_MEX_FILE
   init();
#endif
}*/

void LED_set(uint8_t cmd[])
{
  #ifndef MATLAB_MEX_FILE
   
  set(cmd);
  #endif
}

