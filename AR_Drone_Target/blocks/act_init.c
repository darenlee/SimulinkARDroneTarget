#include "act_init.h"

void Actuator_Initialization ()
{
#ifndef MATLAB_MEX_FILE
   init();
#endif
}

void Actuator_Stop()

{
    #ifndef MATLAB_MEX_FILE
     stop();
    #endif
}    

