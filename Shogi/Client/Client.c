#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock.h>
#include "..\Source\m_sk.h"
#include "..\Source\player.h"

void ControlThread(void*);
void WaitingMatchThread(void*);

void login(SOCKET*, char*);
void waitMatch(SOCKET);

int main() {

	char ID[ID_SIZE];
	SOCKET sk;

	WSADATA wsd;

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return;
	}

	login(&sk, ID);

	
	
	

	ps();

	/*WSADATA wsd;

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return;
	}

	char* ip[30];
	char ID[ID_SIZE];
	int port;
	int reval;
	struct sockaddr_in addr;
	SOCKET sk;
	strcpy(ip, "127.0.0.1");
	port = 123;
	getsocket(&sk);

	createAddr(&addr, ip, port);
	strcpy(ID, "456");
	printf("�s�����A����...\n");
	reval = connectServer(sk, addr);
	send(sk, ID, strlen(ID), 0);
	

	while (1) {
	
		Sleep(100);
	}*/
}


void ControlThread(void *param) {

}
void WaitingMatchThread(void *param) {

	SOCKET sk;
	
	
	while (1) {
		Sleep(1000);
	}


}
void login(SOCKET *sk, char* ID) {

	struct sockaddr_in addr;

	char* ip[30];
	int port;
	int reval;

	printf("�]�w�@���T�G���٩I�Ӿ_��Ĥ�a!\n");
	printf("�A���٩I:");

	//scanf("%s", ID);
	strcpy(ID, "456");


	cls();

	printf("�u�O�Ӥ������٩I %s\n", ID);

	printf("�аݲ{�b�n�i�J����@�Ӧ��A���i�J�t��?\n");

	while (1) {


		printf("IP:");
		
		//scanf("%s", ip);
		strcpy(ip, "127.0.0.1");

		printf("Port:");

		//scanf("%d", &port);
		port = 123;

		cls();

		getsocket(sk);

		createAddr(&addr, ip, port);

		printf("�s�����A����...\n");
		reval = connectServer(*sk, addr);


		if (reval == -1) {
			printf("����...�Э��s��JIP�PPort\n");
		}
		else {
			send(*sk, ID, strlen(ID), 0);
			printf("���\...���ݰt��\n");
			break;
		}
	}
}

