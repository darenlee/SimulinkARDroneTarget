#ifndef _TCP_WINDOWS_SERVER_H
#define _TCP_WINDOWS_SERVER_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <string.h>
	#include <signal.h>
	#include<sys/types.h>

	void closeConnection1(int * serverFdWorkVector);
	void initConnection1(int * serverFdWorkVector, int port);
	double imageReceive1(uint8_t y[1843200], int * workFd);

	void closeConnection2(int * serverFdWorkVector);
	void initConnection2(int * serverFdWorkVector, int port);
	double imageReceive2(uint8_t y[153600], int * workFd);
	
#endif