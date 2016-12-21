
#include "../Source/m_sk.h"
#include "../Source/player.h"



void ControlThread(void *);
void AcceptThread(void *);
void RecvThread(void *);


void buildServer(SOCKET *);
void sendNetworkData(struct playerData *);



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
	printf("│　\u4FE5─傌─相─仕─帥─仕─相─傌─硨　│\n");
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

void AcceptThread(void * param) {

	SOCKET loc;
	SOCKET client;

	struct sockaddr_in addr;
	struct playerData players[2] = { {.sk = -1}, {.sk = -1} };
	struct playerData player;
	

	char buf[ID_SIZE];
	char ID[ID_SIZE];

	int bytes;
	int reval;


	buildServer(&loc);

	_beginthread(ControlThread, 0, &loc);

	printf("伺服器啟動完成，預關閉連線請鍵入quit，等待玩家連入...\n");

	while (1) {
		
		reval = acceptConnect(loc, &client, &addr);
		printf("1");
		if (reval != -1) {

			reval = recvData(client, ID, ID_SIZE);//接收玩家ID

			ID[reval] = '\0';

			printf("玩家[%s]:連入，等待配對\n", ID);

			player.addr = addr;
			player.sk = client;
			strcpy(player.ID, ID);

			_beginthread(RecvThread, 0, addPlayer(players, player));

			if (playerAmount == 2) {
			
				printf("配對 玩家[%s] : 玩家[&s]", players[0].ID, players[1].ID);

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
	
	shutdown(sk,2);
	closesocket(sk);
}

void RecvThread(void *param) {//主要接收玩家是否有收到東西，或者是斷線

	struct playerData *player = (struct playerData *) param;

	SOCKET client = player->sk;

	char* ID = player->ID;
	char buf[BUF_SIZE];

	int reval;


	reval = recvData(client, buf, BUF_SIZE);

	buf[reval] = '\0';

	printf("%d\n", reval);

	if (reval < 0) {

		 
		printf("玩家[%s]斷線\n", player->ID);

	}


	if (strcmp(buf, SUCCESS_GET_DATA)) {
		printf("玩家[%s]成功收到配對資料", ID);
	}

	closesocket(client);

	player->sk = -1;
}



void buildServer(SOCKET *sk) {

	int port;
	int reval;
	struct sockaddr_in addr;

	getsocket(sk);

	printf("建立伺服器，設定Port:");

	port = 123;
	//scanf("%d", &port);

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