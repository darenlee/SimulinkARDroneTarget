#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment (lib, "Ws2_32.lib")
#include "mex.h"

#define DEFAULT_BUFLEN 131072

#include "tcpWindowsServer.h"


/******************************************
			  TCP FUNCTIONS
******************************************/

static CHAR * getLastErrorText(CHAR *pBuf, ULONG bufSize)
{
    DWORD retSize;
    LPTSTR pTemp=NULL;

    retSize=FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
                          FORMAT_MESSAGE_FROM_SYSTEM|
                          FORMAT_MESSAGE_ARGUMENT_ARRAY,
                          NULL,
                          GetLastError(),
                          LANG_NEUTRAL,
                          (LPTSTR)&pTemp,
                          0,
                          NULL);
     if (!retSize || pTemp == NULL) {
          pBuf[0]='\0';
     } else {
          pTemp[strlen(pTemp)-2]='\0'; //remove cr and newline character
          sprintf(pBuf,"%0.*s (0x%x)",bufSize-16,pTemp,GetLastError());
          LocalFree((HLOCAL)pTemp);
     }
     return(pBuf);
}


 
char err[255];
int open_TCPserver(int tport)
{


	WSADATA wsaData;
    int iResult;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL;
    struct addrinfo hints;
 
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        sprintf(err, "WSAStartup failed with error: %d\n", iResult);
        return -1;
    }
	
	
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
	char sport[10];
	_itoa(tport, sport, 10);
    iResult = getaddrinfo(NULL, sport, &hints, &result);
    if ( iResult != 0 ) {
        sprintf(err, "WSAStartup failed with error: %d\n", iResult);
        WSACleanup();
        return -1;
    }

	
    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        sprintf(err, "socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }

	
    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        sprintf(err, "bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return -1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        sprintf(err, "listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return -1;
    }

	return (int) ListenSocket;
}


int accept_TCPserver(SOCKET ListenSocket)
{
	
	SOCKET ClientSocket = INVALID_SOCKET;

	ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        sprintf(err, "accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return -1;
    }
	
	int sndsize = DEFAULT_BUFLEN; 
	int error = setsockopt(ClientSocket, SOL_SOCKET, SO_RCVBUF, (char *)&sndsize, (int)sizeof(sndsize));
	
	error = setsockopt(ClientSocket, SOL_SOCKET, SO_RCVBUF, (char *)&sndsize, (int)sizeof(sndsize)); 
	
	return ClientSocket;
	
}


int TCP_receive(int fd, char *buffer, int bytes)
{

	int iResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
	int nRead = 0;
	int nleft = bytes;
	
	do {
        iResult = recv(fd, recvbuf, recvbuflen, 0);
        if ( iResult > 0 ){
			memcpy(buffer+nRead, recvbuf, iResult);
			nRead += iResult;
			nleft -= iResult;
			memset(recvbuf,'\0',recvbuflen);
		} else if ( iResult == 0 )
            break;
        else
            printf("recv failed: %d\n", WSAGetLastError());
    } while( nleft > 0);

	return nRead;
}









/******************************************
				VIDEO 1
******************************************/


void closeConnection1(int * serverFdWorkVector)
{
	closesocket(serverFdWorkVector[0]);
	return;
}


void initConnection1(int * serverFdWorkVector, int port){
	int fd = open_TCPserver(port);
	serverFdWorkVector[0] = fd; 
	return;
}


double imageReceive1(uint8_t y[1843200], int * workFd){

	double nbytes = 0;
	
	int fd = accept_TCPserver( (SOCKET) workFd[0]); 
	nbytes = TCP_receive(fd, y, 1843200); 
	closesocket(fd);
	
	return nbytes; 
}






/******************************************
				VIDEO 2
******************************************/


void closeConnection2(int * serverFdWorkVector)
{
	closesocket(serverFdWorkVector[0]);
	return;
}


void initConnection2(int * serverFdWorkVector, int port){
	int fd = open_TCPserver(port);
	serverFdWorkVector[0] = fd; 
	return;
}


double imageReceive2(uint8_t y[153600], int * workFd){

	double nbytes = 0;
	
	int fd = accept_TCPserver( (SOCKET) workFd[0]); 
	nbytes = TCP_receive(fd, y, 153600); 
	closesocket(fd);
	
	return nbytes; 
}