#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock.h>
#include "..\Source\m_sk.h"
#include "..\Source\player.h"

void ControlThread(void*);


void buildServer(SOCKET, int);
void connectMate(SOCKET, struct userData, int);
void login(SOCKET*, char*);
struct userData waitMatch(SOCKET);



int main() {

	char ID[ID_SIZE];
	SOCKET sk;
	int port;
	int len = sizeof(struct sockaddr_in);
	struct sockaddr_in loc_addr;
	struct userData mate_data;

	WSADATA wsd;

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return;
	}


	login(&sk, ID);

	getsockname(sk, (struct sockaddr*)& loc_addr, &len);

	port = ntohs(loc_addr.sin_port);

	printf("%d\n", port);

	mate_data = waitMatch(sk);
	
	closesocket(sk);
	
	getsocket(&sk);

	if (mate_data.length == -1) {
		printf("Server斷線，無法配對，正在關閉程式...");
		ps();
		exit(-1);
	}
	else {
		printf("配對成功，收到對戰者資訊...\n");
		printf("對手名子: %s\n", mate_data.ID);
		printf("對手PORT: %d\n", ntohs(mate_data.addr.sin_port));
		
	}
	
	connectMate(&sk, mate_data, port);
	while (1) {

		Sleep(100);
	}
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
	printf("連接伺服器中...\n");
	reval = connectServer(sk, addr);
	send(sk, ID, strlen(ID), 0);
	

	while (1) {
	
		Sleep(100);
	}*/
}


void ControlThread(void *param) {

}

void buildServer(SOCKET* sk, int port){
	

	int reval;

	printf("建構伺服器中...");

	reval = createServer(*sk, port, 1);
	if (reval == -1) {
		printf("失敗\n");
		ps();
		exit(-1);
	}
	printf("等待對手連入\n");
	

}

void connectMate(SOCKET* sk, struct userData mate_data, int port)
{
	SOCKET mate;
	struct sockaddr_in mate_addr;
	int reval;

	if (mate_data.isServer) {
	

		buildServer(sk , port);

		reval =	acceptConnect(*sk, &mate, &mate_addr);

	}
	else{

		reval = connectServer(*sk, mate_data.addr);
	}

	if (reval == -1) {
	
		printf("連接對手失敗，無法進行對戰...\n");
	}
	else {
	
		printf("開始對戰...\n");
	}



}

void login(SOCKET *sk, char* ID) {

	struct sockaddr_in addr;

	char* ip[30];
	int port;
	int reval;

	printf("設定一個響亮的稱呼來震懾敵手吧!\n");
	printf("你的稱呼:");

	//scanf("%s", ID);
	strcpy(ID, "456");


	cls();

	printf("真是個不錯的稱呼 %s\n", ID);

	printf("請問現在要進入到哪一個伺服器進入配對?\n");

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

		printf("連接伺服器中...\n");
		reval = connectServer(*sk, addr);


		if (reval == -1) {
			printf("失敗...請重新輸入IP與Port\n");
		}
		else {
			send(*sk, ID, strlen(ID), 0);
			printf("成功...等待配對\n");
			break;
		}
	}
}

struct userData waitMatch(SOCKET sk) {

	char* buf[sizeof(struct userData)];
	struct userData ud = {.length = -1};
	int reval; 

	reval = recvData(sk, buf, sizeof(struct userData), 0);

	if (reval > 0) {

		memcpy(&ud, buf, sizeof(struct userData));

		ud.ID[ud.length] = '\0';
	}
	return ud;
}