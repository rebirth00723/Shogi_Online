
#include "../Source/m_sk.h"
#include "../Source/player.h"



void ControlThread(void *);
void AcceptThread(void *);
void RecvThread(void *);


void buildServer(SOCKET *);
void sendNetworkData(struct playerData *);



int main() {

	WSADATA wsd;
	struct playerData players[2] = { { .sk = -1 },{ .sk = -1 } };

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return;
	}


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

	WaitForSingleObject(_beginthread(AcceptThread, 0, players), INFINITE);

	WSACleanup();
	system("pause");
}

void AcceptThread(void * param) {

	SOCKET loc;
	SOCKET client;

	struct sockaddr_in addr;
	struct playerData* players = (struct playerData *)param;
	struct playerData player;
	

	char buf[ID_SIZE];
	char ID[ID_SIZE];

	int bytes;
	int reval;


	buildServer(&loc);

	_beginthread(ControlThread, 0, &loc);//Thread

	printf("伺服器啟動完成，預關閉連線請鍵入quit，等待玩家連入...\n");

	while (1) {
		
		reval = acceptConnect(loc, &client, &addr);

		if (reval < 0) {
			printf("關閉伺服器\n");
			break;
		}
		else {

			reval = recvData(client, ID, ID_SIZE);//接收玩家ID

			ID[reval] = '\0';

			int port;

			port = ntohs(addr.sin_port);

			printf("玩家[%s]:連入，等待配對，%d\n", ID, port);

			player.addr = addr;
			player.sk = client;
			strcpy(player.ID, ID);

			_beginthread(RecvThread, 0, addPlayer(players, player));//Thread

			printf("當前玩家數量 :%d\n", playerAmount(players));

			if (playerAmount(players) == 2) {
			
				printf("配對 玩家[%s] : 玩家[%s]\n", players[0].ID, players[1].ID);

				sendNetworkData(players);
			
			}
		}
		
	}//while

	
}


void ControlThread(void * param){

	SOCKET sk = *(SOCKET *)param;
	char cmd[120];
	

	while (1) {
	
		scanf("%s", cmd);
		if (!strcmp(cmd, "quit"))
			break;
	}
	Sleep(1000);
	printf("close");

	shutdown(sk, 2);
	closesocket(sk);
}

void RecvThread(void *param) {//主要接收玩家是否有收到東西，或者是斷線

	struct playerData *player = (struct playerData *) param;

	SOCKET client = player->sk;

	char* ID = player->ID;
	char buf[BUF_SIZE];

	int reval;


	reval = recvData(client, buf, BUF_SIZE);

	
	
	if (reval < 0) {

			
			printf("玩家[%s]斷線\n", ID);
			player->sk = -1;
		
	}
	else if(reval == 0) {
		printf("玩家[%s]成功收到配對資料\n", ID);
		
	}

	shutdown(client, 2);
	closesocket(client);

	
}



void buildServer(SOCKET *sk) {

	int port;
	int reval;
	struct sockaddr_in addr;

	getsocket(sk);

	printf("建立伺服器，設定Port:");

	scanf("%d", &port);

	cls();

	printf("建構伺服器中...");

	reval = createServer(*sk, port, 3);
	if (reval == -1) {
		printf("失敗\n");
		ps();
		exit(-1);
	}	
	printf("成功\n");


	cls();
}

void sendNetworkData(struct playerData* players) {

	struct userData p1, p2;

	

	char* buf[sizeof(struct playerData)];



	p1.addr = players[0].addr;
	strcpy(p1.ID, players[0].ID);

	p2.addr = players[1].addr;
	strcpy(p2.ID, "123");

	p1.length = strlen(p1.ID);
	p2.length = strlen(p2.ID);

	p1.isServer = false;
	p2.isServer = true;


	memcpy(buf, &p2, sizeof(p2));
	send(players[0].sk, buf, sizeof(buf), 0);

	memcpy(buf, &p1, sizeof(p1));
	send(players[1].sk, buf, sizeof(buf), 0);

	clrPlayer(players);
}