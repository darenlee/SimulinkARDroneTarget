/*
versionCheck.c 

This code is used to check whether the AR Drone is running firmware which is known to be compatible
*/

#ifndef MATLAB_MEX_FILE

#include <stdio.h>

#endif //MATLAB_MEX_FILE

#include "versionCheck.h"

static unsigned char isSupported = 1;

void versionCheckInit(void)
{
#ifndef MATLAB_MEX_FILE
    isSupported = 1;
	FILE *fp;
	char versionString[] = "2.4.8";
	int versionStringLength = 5;
	char ch;
	int count = 0;

	fp = fopen("/firmware/version.txt", "r");
	if (fp == NULL)
	{
		printf("Error: Could not locate /firmware/version.txt");
	}
	else
	{
		while ((ch = fgetc(fp)) != EOF && count < versionStringLength)
		{
			if (ch != versionString[count])
			{
				printf("Warning: The AR Drone Target has only been tested to work on the AR Drone 2.0 Running firmware 2.4.8. The target Drone appears to have a different firmware version.");
                isSupported = 0;
				break;
			}
			count++;
		}	
	}
#endif //MATLAB_MEX_FILE
}

void versionCheckStep(unsigned char* supported)
{
#ifndef MATLAB_MEX_FILE
    *supported = isSupported;
#endif //MATLAB_MEX_FILE
}

void versionCheckClose(void)
{
#ifndef MATLAB_MEX_FILE
#endif //MATLAB_MEX_FILE
}