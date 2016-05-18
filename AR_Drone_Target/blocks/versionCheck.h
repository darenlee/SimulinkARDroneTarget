/*
versionCheck.h

*/

#ifndef _VERSIONCHECK_H
#define _VERSIONCHECK_H

#ifndef MATLAB_MEX_FILE
#endif //MATLAB_MEX_FILE

void versionCheckInit(void);
void versionCheckStep(unsigned char* supported);
void versionCheckClose(void);
#endif