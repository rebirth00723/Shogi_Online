#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <stdbool.h>
#include "m_sk.h"

#define FILE_NOT_FOUND (HANDLE)0xFFFFFFFFF

#pragma warning(disable: 4996)
#pragma comment (lib, "wsock32.lib")


int acceptConnect(SOCKET listen, SOCKET * connect, struct sockaddr_in* conn_addr) {

	int reval;
	int len = 16;

	reval = accept(listen, (struct sockaddr *) conn_addr, &len);

	checkError(reval, "acceptConnect");

	return *connect = reval;
}

int bindsocket(SOCKET sk, struct sockaddr_in* addr) {

	int reval;
	reval = bind(sk, (struct sockaddr *) addr, 16);
	return checkError(reval, "bindsock");
}


int checkError(int error, char* str) {

	if (error == -1)
		printf("\n%s faild! Error Code:%d\n", str, WSAGetLastError());
	return error;
}


void createAddr(struct sockaddr_in* addr, char* ip, int port) {

	addr->sin_family = AF_INET;
	addr->sin_port = htons((short)port);
	addr->sin_addr.s_addr = inet_addr(ip);

}


void createAddrA(struct sockaddr_in* addr, int port) {

	addr->sin_family = AF_INET;
	addr->sin_port = htons((short)port);
	addr->sin_addr.s_addr = htonl(INADDR_ANY);

}


int createServer(SOCKET sk, int port, int backlog) {

	struct sockaddr_in server_addr;
	int reval = 1;

	for (int i = 0; i < 1; i++) {

		createAddrA(&server_addr, port);

		reval = bindsocket(sk, &server_addr);
		if (reval == -1) break;

		reval = listensocket(sk, backlog);
		if (reval == -1) break;

	}
	return reval;
}


int connectServer(SOCKET sk, struct sockaddr_in addr) {

	int reval;


	reval = connect(sk, (struct sockaddr*)&addr, 16);

	checkError(reval, "connectServer");
	return reval;
}

void getDataList(char* datalist,char* str) {

	HANDLE hdl;
	WIN32_FIND_DATA fl;
	char tmp[128];
	
	datalist[0] = '\0';

	hdl = FindFirstFile(str, &fl);

	if (hdl != FILE_NOT_FOUND) {

		do {
			if ((fl.dwFileAttributes & 0x0010) != 0)
				sprintf(tmp, "[%s]", fl.cFileName);
			else
				sprintf(tmp, "%s", fl.cFileName);


			strcat(datalist, tmp);
			strcat(datalist, "\n");

		} while (FindNextFile(hdl, &fl));
	}

	FindClose(hdl);

	return datalist;
}
void getsocket(SOCKET* sk) {


	*sk = socket(AF_INET, SOCK_STREAM, 0);

	if (*sk == -1)
		closesocket(*sk);

	checkError((int)*sk, "getsocket");
	
}

int hasData(char* filename) {

	HANDLE hdl;
	WIN32_FIND_DATA fl;
	int reval = 1;

	hdl = FindFirstFile(filename, &fl);

	if (hdl == INVALID_HANDLE_VALUE)
		reval = 0;
	
	FindClose(hdl);

	return reval;
}
int listensocket(SOCKET sk, int backlog) {

	int reval;
	reval = listen(sk, backlog);

	return checkError(reval, "listensocket");
}
int recvData(SOCKET sk, char* buf, int len) {

	int reval;
	reval = recv(sk, buf, len, 0);
	//checkError(reval, "recvData");
	return reval;
}