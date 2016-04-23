#ifndef _TCP_LINUX_CLIENT_H
#define _TCP_LINUX_CLIENT_H

	#ifndef MATLAB_MEX_FILE

		#include <stdio.h>
		#include <stdlib.h>
		#include <stdint.h>
		#include<sys/types.h>

		int 	TCP_client_linux(char * ip ,long port);
		int 	TCP_send_linux(int fd, char * message, int length);

		void 	imageCloseConnection1(int fd);
		void 	imageInitConnection1(int * clientPortWorkVector, int port);
		double 	imageSend1(unsigned char* imageVectorInput, int * clientPortWorkVector);

		void imageCloseConnection2(int fd);
		void imageInitConnection2(int * clientPortWorkVector, int port);
		double imageSend2(unsigned char* imageVectorInput, int * clientPortWorkVector);

	#endif //MATLAB_MEX_FILE

#endif

