#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock.h>
#include "../Source/m_sk.h"
#include "../Source/player.h"



void ControlThread(void *);
void AcceptThread(void *);
void RecvThread(void *);


void buildServer(SOCKET *);
void sendNetworkData(struct playerData *);

struct recv {

	SOCKET sk;
	struct playerData* player;

};



int main() {

	WSADATA wsd;

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return;
	}

	int playerID;
	printf("┌───────────────────┐\n");
	printf("│　　　　　　　　　　　　　　　　　　　│\n");
	printf("│　硨─傌─相─仕─帥─仕─相─傌─硨　│\n");
	printf("│　│　│　│　│╲│╱│　│　│　│　│\n");
	printf("│　├─┼─┼─┼─┼─┼─┼─┼─┤　│\n");
	printf("│　│　│　│　│╱│╲│　│　│　│　│\n");
	printf("│　├─炮─┼─┼─┼─┼─┼─炮─┤　│\n");
	printf("│　│　│　│　│　│　│　│　│　│　│\n");
	printf("│　兵─┼─兵─┼─兵─┼─兵─┼─兵　│\n");
	printf("│　│　│　│　│　│　│　│　│　│　│\n");
	printf("│　├─┴─┴─┴─┴─┴─┴─┴─┤　│\n");
	printf("│　│　　楚　河　　　　　漢　界　　│　│\n");
	printf("│　├─┬─┬─┬─┬─┬─┬─┬─┤　│\n");
	printf("│　│　│　│　│　│　│　│　│　│　│\n");
	printf("│　卒─┼─卒─┼─卒─┼─卒─┼─卒　│\n");
	printf("│　│　│　│　│　│　│　│　│　│　│\n");
	printf("│　├─包─┼─┼─┼─┼─┼─包─┤　│\n");
	printf("│　│　│　│　│╲│╱│　│　│　│　│\n");
	printf("│　├─┼─┼─┼─┼─┼─┼─┼─┤　│\n");
	printf("│　│　│　│　│╱│╲│　│　│　│　│\n");
	printf("│　車─馬─象─士─將─士─象─馬─車　│\n");
	printf("│　　　　　　　　　　　　　　　　　　　│\n");
	printf("└───────────────────┘\n");

	WaitForSingleObject(_beginthread(AcceptThread, 0, NULL), INFINITE);

	WSACleanup();
	system("pause");
}

void ControlThread(void * param){

	char* cmd[4];
	boolean *stop = (boolean *)param;

	while (1) {
	
		gets_s(cmd, sizeof(cmd));
		if (!strcmp(cmd, "quit"))
			break;
	}

	*stop = true;
}

void AcceptThread(void * param){

	SOCKET loc;
	SOCKET client;

	struct sockaddr_in addr;
	struct playerData playerData;
	struct playerData players[2];
	struct recv rd;
	char buf[ID_SIZE];
	int bytes;
	int reval;
	int connecngti;

	boolean stop;

	stop = false;

	buildServer(&loc, &stop);

	printf("伺服器啟動完成，預關閉連線請鍵入quit，等待玩家連入...\n");

	while ( ! stop) {
		
		reval = acceptConnect(loc, &client, &addr);
		recvData(client, buf, 15);//接收玩家ID


		if (reval != -1) {

			playerData.addr = addr;
			playerData.sk = loc;
			strcpy(playerData.ID, buf);

			

			rd.player = addPlayer(players, playerData);;
			rd.sk = client;

			_beginthread(RecvThread, 0, &rd);

			printf("玩家[%d]:連入，等待配對\n");
			

			if (playerAmount == 2) {
				
				printf("配對 玩家[%s] : 玩家[&s]", players[0].ID, players[1].ID);
				
				sendNetworkData(players);				
				
			}


		
		}//if
	}//while
}

void RecvThread(void *param) {

	struct recv r= *(struct recv*) param;
	struct playerData* player = r.player;
	SOCKET sk = r.sk;
	
	int reval;

	char buf[BUF_SIZE];
			
	reval = recvData(sk, buf, BUF_SIZE);

	buf[reval] = '\0';

	if (reval < 0) {
			
		player->sk = -1;
		printf("玩家[%s]斷線\n", player->ID);
			
	}


	if (strcmp(buf, SUCCESS_GET_DATA)) {
		printf("玩家[%s]成功收到配對資料", player->ID);
	}

	
	closesocket(player->sk);
}


void buildServer(SOCKET *sk, boolean *stop) {

	int port;
	int reval;
	struct sockaddr_in addr;

	getsocket(sk);

	printf("建立伺服器，設定Port:");
	scanf("%d", &port);

	cls();

	Sleep(1000);
	printf("建構伺服器中...");

	reval = createServer(*sk, port, 3);
	if (reval == -1) {
		printf("失敗\n");
		ps();
		exit(-1);
	}	
	printf("成功\n");

	Sleep(1000);

	cls();

	_beginthread(ControlThread, 0, stop);
}

void sendNetworkData(struct playerData* players) {

	struct userData p1, p2;

	

	int buf[sizeof(struct playerData)];
	int r;

	r = rand() % 2;

	if (r == 0) {
		p1.addr = players[0].addr;//改改看!r
		strcpy(p1.ID, players[0].ID);
		p2.addr = players[1].addr;//改改看!r
		strcpy(p2.ID, players[1].ID);
	}else{
		p1.addr = players[1].addr;//改改看!r
		strcpy(p1.ID, players[1].ID);
		p2.addr = players[2].addr;//改改看!r
		strcpy(p2.ID, players[2].ID);
	}
	p1.isServer = true;
	p2.isServer = false;
	memcpy(buf, &p1, sizeof(p1));

	send(players[1].sk, buf, sizeof(buf), 0);

	memcpy(buf, &p2, sizeof(p2));

	send(players[2].sk, buf, sizeof(buf), 0);

	closesocket(players[0].sk);
	closesocket(players[1].sk);

	clrPlayer(players);
}