/**
 * @file linuxUDP.c
 * Copyright 2009-2013 The MathWorks, Inc.
 */

#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include "HostLib_Network.h"
#include "rtwtypes.h"


typedef struct tgtsockstruct {
    int sockfd;
    struct sockaddr_in localsockaddr;
    struct sockaddr_in remotesockaddr;
    int dataTypeSize;
} TgtSockStructT;


void TGT_libCreate(void **device_, char *err, NetworkInputOrOutput io, 
       const char *localURL, int localPort, const char *remoteURL, 
       int remotePort, int bufferSize, int dataTypeSize, int blockingTime);
void TGT_libUpdate(void *device, char *err, const void *src, int nSamples);
void TGT_libStart(void *device, char *err);
void TGT_libOutputs(void *device, char *err, void *src, int *nSamples);
void TGT_libTerminate(void *device, char *err);
void TGT_libDestroy(void *device, char *err, int type);


void CreateTargetUDPInterface(void *hl) 
{
    HostLibrary *hostLib = (HostLibrary*)hl;
    *hostLib->errorMessage = '\0';
    memset(hostLib, 0, sizeof(HostLibrary));

    /* Indicate that the structure is valid for future function calls. */    
    hostLib->library      = (void*) 1;
    
    /* Set the function pointers to point to target UDP implementation. */    
    hostLib->libCreate    = (void*) TGT_libCreate;
    hostLib->libStart     = (void*) TGT_libStart; 
    hostLib->libReset     = (void*) NULL; 
    hostLib->libUpdate    = (void*) TGT_libUpdate;
    hostLib->libOutputs   = (void*) TGT_libOutputs;
    hostLib->libTerminate = (void*) TGT_libTerminate;
    hostLib->libDestroy   = (void*) TGT_libDestroy;
}


void DestroyTargetUDPInterface(void *hl) 
{
    HostLibrary *hostLib = (HostLibrary*)hl;
    if(hostLib->library) {
        /* Clear the structure (except for any possible error message). */
		memset(hostLib, 0, sizeof(HostLibrary) - MAX_ERR_MSG_LEN);
    }
}


void TGT_libCreate(void **device_, char *err, NetworkInputOrOutput io, 
       const char *localURL, int localPort, const char *remoteURL, 
       int remotePort, int bufferSize, int dataTypeSize, int blockingTime)
{
    int flags;
    struct timeval tv;
    int ret;
    TgtSockStructT *device;
    device = (TgtSockStructT *) malloc (sizeof(TgtSockStructT)); 
    
    
      if (dataTypeSize < sizeof(int))
      {
          /* LINUX Kernel returns EINVAL for setsockopt 
             if optval is less than sizeof(int)
           */
          dataTypeSize = sizeof(int);
      }
    bzero(&device->remotesockaddr, sizeof(device->remotesockaddr));
    device->remotesockaddr.sin_family = AF_INET;
    device->remotesockaddr.sin_port = htons(remotePort);
    inet_aton(remoteURL, &device->remotesockaddr.sin_addr);
    
    bzero(&device->localsockaddr, sizeof(device->localsockaddr));
    device->localsockaddr.sin_family = AF_INET;
    device->localsockaddr.sin_port = htons(localPort);
    inet_aton(localURL, &device->localsockaddr.sin_addr); 
    
    device->sockfd = socket(AF_INET, SOCK_DGRAM, 0);    
    if (device->sockfd<0)
        printf ("error creating socket\n");

    ret = setsockopt(((TgtSockStructT *) device)->sockfd, SOL_SOCKET,
                SO_RCVBUF, &bufferSize, dataTypeSize);

    if (ret < 0)
    {
        perror("ERROR in setsockopt");
    }
    
    if(blockingTime == 0) { 
        /* set non-blocking socket option */
        flags = fcntl(((TgtSockStructT *) device)->sockfd, F_GETFL, 0);
        fcntl(((TgtSockStructT *) device)->sockfd, F_SETFL, flags | O_NONBLOCK);      
    }
    else if(blockingTime != MIN_int32_T) 
    { 
        /* if not set to inf in the block mask */
        tv.tv_sec  = (long) (blockingTime/1000);
        tv.tv_usec = (long) (blockingTime % 1000);    
        setsockopt(((TgtSockStructT *) device)->sockfd, SOL_SOCKET, 
                SO_RCVTIMEO, &tv, sizeof(tv));
    }       

    device->dataTypeSize = dataTypeSize;

    *device_ = device;

    err[0] = '\0';
}


void TGT_libStart(void *device, char *err) 
{
    if(device) {
        bind(((TgtSockStructT *) device)->sockfd, 
             (struct sockaddr *) &((TgtSockStructT *) device)->localsockaddr, 
             sizeof(((TgtSockStructT *) device)->localsockaddr));
    }
}


void TGT_libUpdate(void *device, char *err, const void *src, int nSamples)
{
    int n;  
    if(device) {   
        n = sendto(((TgtSockStructT *) device)->sockfd, src, 
                   ((TgtSockStructT *) device)->dataTypeSize * nSamples, 0, 
                   (struct sockaddr *) &((TgtSockStructT *) device)->remotesockaddr, 
                   sizeof(((TgtSockStructT *) device)->remotesockaddr));
        /* if(n<0)
         * printf("error writing to socket\n");
         */
    }
}


void TGT_libOutputs(void *device, char *err, void *src, int *nSamples)
{
    int n = 0;
    if(device) {
        n = recvfrom(((TgtSockStructT *) device)->sockfd, src, 
                     ((TgtSockStructT *) device)->dataTypeSize * (*nSamples), 
                     0, NULL, NULL);
        if (n > 0) {
            *nSamples = n; /* Return number of bytes received */
        }
        else {
            *nSamples = 0; /* No UDP packets received */
        }
    }
}


void TGT_libTerminate(void *device, char *err)
{
    /* NOP; */
}


void TGT_libDestroy(void *device, char *err, int type) 
{
    if(device)
        free(device);
}
