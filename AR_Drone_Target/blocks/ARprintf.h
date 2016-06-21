/*
    ARprintf.c - cp driver

*/

#ifndef _ARPRINT_H
#define _ARPRINT_H

#ifndef MATLAB_MEX_FILE
#endif //MATLAB_MEX_FILE

void ARpintf_Init(void);
void ARpintf_Close(void);
void ARpintf_Update(double char2print);
#endif