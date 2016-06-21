/*
    ARprintf.c - cp driver

*/

#ifndef MATLAB_MEX_FILE

#include <stdio.h>

#endif //MATLAB_MEX_FILE

#include "ARprintf.h"

void ARpintf_Init(void)
{
#ifndef MATLAB_MEX_FILE
#endif //MATLAB_MEX_FILE
}

void ARpintf_Close(void)
{
#ifndef MATLAB_MEX_FILE
#endif //MATLAB_MEX_FILE
}

void ARpintf_Update(double char2print) {
	
#ifndef MATLAB_MEX_FILE
	printf("char2print = %f\n", char2print);
#endif //MATLAB_MEX_FILE
}