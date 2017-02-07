#ifndef MATLAB_MEX_FILE

//#include <signal.h>


#endif //MATLAB_MEX_FILE



#ifndef MATLAB_MEX_FILE

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <getopt.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h> 
#include <linux/videodev2.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#endif //MATLAB_MEX_FILE

#include "tcpLinuxClient.h"
#define DEFAULT_BUFLEN 131072








/******************************************
			  TCP FUNCTIONS
******************************************/

#ifndef MATLAB_MEX_FILE
int TCP_client_linux(char * ip ,long port)
{						
	void (*old_handler)(int);
	int n; 
	char *ptr, buffer[1024]; 
	struct sockaddr_in addr; 

	if((old_handler=signal(SIGPIPE,SIG_IGN))==SIG_ERR){ 
		printf("signal error\n");
		exit(1);
	} 
	int fd = socket(AF_INET,SOCK_STREAM,0);
	
	if(fd == -1){
		printf("socket returned -1\n");
		exit(1);
	} 
	
	memset((void*)&addr,(int)'\0',sizeof(addr));

	addr.sin_family=AF_INET; 
	inet_aton(ip, &addr.sin_addr);
	addr.sin_port=htons(port);
  
	int err;
	int sndsize = DEFAULT_BUFLEN; 
	int sockbufsize = 0;
	int iSock = 1;
	err = setsockopt( fd, IPPROTO_TCP, TCP_QUICKACK, (void *)&iSock, sizeof(iSock));
	err = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char *)&sndsize, (int)sizeof(sndsize)); 
	err = setsockopt(fd, IPPROTO_TCP, TCP_MAXSEG, (char *)&sndsize, (int)sizeof(sndsize)); 
  
	n=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(n==-1) return -1;
	
	return fd;
}

int TCP_send_linux(int fd, char * message, int length)
{
	char * ptr = message;
	int nleft,nwritten, n;
	nwritten = 0;
	nleft=length; 
	while(nleft>0){
		if(nleft < 8192) n=write(fd, ptr, nleft); 
		else n=send(fd, ptr, 8192, 0); 
		if(n==-1){
			return -1;
		}
		nleft-=n; 
		ptr+=n;
		nwritten += n;
	} 
	return nwritten;
}
#endif //MATLAB_MEX_FILE









/******************************************
				VIDEO 1
******************************************/

void imageCloseConnection1(int fd){
	#ifndef MATLAB_MEX_FILE

	#endif //MATLAB_MEX_FILE
}


void imageInitConnection1(int * clientPortWorkVector, int port)
{
#ifndef MATLAB_MEX_FILE
	clientPortWorkVector[0] = port;
	return;
#endif //MATLAB_MEX_FILE

}


double imageSend1(unsigned char* imageVectorInput, int * clientPortWorkVector)
{
#ifndef MATLAB_MEX_FILE
	double nbytes = 0;
	int s = TCP_client_linux("192.168.1.2", clientPortWorkVector[0]);
	
	if(s!=-1){
		nbytes = TCP_send_linux(s,(char *) imageVectorInput, 1843200);
		close(s);
	} 
		
	return nbytes;
#endif //MATLAB_MEX_FILE
}





/******************************************
				VIDEO 2
******************************************/

void imageCloseConnection2(int fd){
	#ifndef MATLAB_MEX_FILE

	#endif //MATLAB_MEX_FILE
}


void imageInitConnection2(int * clientPortWorkVector, int port)
{
#ifndef MATLAB_MEX_FILE
	clientPortWorkVector[0] = port;
	return;
#endif //MATLAB_MEX_FILE

}


double imageSend2(unsigned char* imageVectorInput, int * clientPortWorkVector)
{
#ifndef MATLAB_MEX_FILE
	double nbytes = 0;
	int s = TCP_client_linux("192.168.1.2", clientPortWorkVector[0]);
	
	if(s!=-1){
		nbytes = TCP_send_linux(s,(char *) imageVectorInput, 153600);
		close(s);
	} 
		
	return nbytes;
#endif //MATLAB_MEX_FILE
}


