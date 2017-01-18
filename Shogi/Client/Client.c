#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock.h>
#include <windows.h>
#include "..\Source\shogi.h"
#include "..\Source\m_sk.h"
#include "..\Source\player.h"

typedef struct {

	int piece;
	int x;
	int y;

}CHANGE;
int  choose();

void ControlThread(void*);

void Apress(shogi *s, struct userData mate_data, SOCKET sk);
void Brefresh(shogi *s, struct userData mate_data, SOCKET sk);
void buildServer(SOCKET*, int);

void connectMate(SOCKET*, struct userData, int);
void gotoxy(int, int);
void login(SOCKET*, char*);
void pressPiece(shogi *s, struct userData mate_data, SOCKET sk);

struct userData waitMatch(SOCKET);

void test() {

	shogi s = initShogi(0);

	s.print(s);
	system("pause");
}

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


	connectMate(&sk, mate_data, port);

	Sleep(500);
	cls();

	shogi s = initShogi(mate_data.isServer);

	while (1) {

		s.print(s);
	
		pressPiece(&s, mate_data, sk);

	




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


int choose()
{
	HANDLE handle;
	DWORD cnt;//儲存出入
	DWORD mode;//Console Mode
	INPUT_RECORD input;
	int x = 0, y = 0;
	POS start = { -1,-1 };
	POS end = { -1,-1 };
	handle = GetStdHandle(STD_INPUT_HANDLE);//先取得基本輸入Handle
	GetConsoleMode(handle, &mode);//得到基本輸入的Mode
	SetConsoleMode(handle, mode & ~ENABLE_LINE_INPUT);//設定基本輸入模式，其中~ENABLE_LINE_INPUT代表不用按下Enter也可動作

	gotoxy(0, 0);//預計設定好案件

	while (ReadConsoleInput(handle, &input, 1, &cnt))//開始讀取使用者的動作
	{
		if (input.EventType == KEY_EVENT)
		{
			if (input.Event.KeyEvent.bKeyDown == TRUE)
			{
				if (input.Event.KeyEvent.wVirtualKeyCode == VK_SPACE)//space
					if (start.x == -1) {
						start.x = x;
						start.y = y;
					}
					else {
						end.x = x;
						end.y = y;
						break;
					}

				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)//Esc
					start.x = -1;
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)//left
					x--;
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)//right
					x++;
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_UP)//up
					y--;
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)//down
					y++;
				gotoxy(x, y);
			}
		}
	}
	return 1;
}

void ControlThread(void *param) {

}


void Apress(shogi *s, struct userData mate_data, SOCKET sk)
{

	int id = 0;
	int lock = 1;
	printf("\n請下棋\n\n");

	

	while (lock) {
		choose();

		
		/*
		s->showSurvive(*s);
		printf("\n輸入棋子編號:");
		scanf("%d", &id);
		getchar();
		if (id < 0 || id >16) {
			cls();
			s->print(*s);
			printf("\n輸入錯誤, 重新輸入...\n");
			continue;
		}

		if (s->pos[1][id].x == -1) {
			cls();
			s->print(*s);
			printf("\n該棋子已陣亡, 重新輸入...\n");
			continue;
		
		}

		
		lock = 0;
		cls();
		s->print(*s);
		while (1) {

			int val;
			char x;
			int y = 0;
			char piece[2];
			
			getPiece(id, piece, s->isblack);

			printf("\n您目前選擇的棋子 %c%c(%c,%d) \n", piece[0], piece[1], 'A'  + s->pos[1][id].x, s->pos[1][id].y);
			printf("輸入移動座標 ex: J 6 (重新選擇輸入 0 0):");
			scanf("%c %d", &x, &y);
			getchar();
			if ( x == '0' && y == 0) {
				cls();
				s->print(*s);
				printf("\n重新選擇棋子\n\n");
				lock = 1;
				break;
			}
			if (x < 'A' || x> 'J' || y < 0 || y>9) {
				cls();
				s->print(*s);
				printf("\n輸入錯誤，重新輸入...\n");
				continue;
			}

			val = s->move(s, id, x-'A', y);

			if (val == 0) {
				cls();
				s->print(*s);
				printf("\n移動失敗，重新移動...\n");
				continue;
			}
			cls();
			s->print(*s);

			break;
		}*/
	}

}

void Brefresh(shogi *s, struct userData mate_data, SOCKET sk)
{
	printf("等待對方下棋\n");



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
void gotoxy(int xpos, int ypos)
{
	if (xpos < 0 || xpos > 8 || ypos < 0 || ypos > 9)
		return;
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = offset(xpos)*2; scrn.Y = offset(ypos);
	SetConsoleCursorPosition(hOuput, scrn);
} //接著輸入這個函式,這樣就可以在其他函式使用了


void login(SOCKET *sk, char* ID) {

	struct sockaddr_in addr;

	char* ip;
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
		ip = "127.0.0.1";

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

void pressPiece(shogi *s, struct userData mate_data, SOCKET sk)
{
	if (s->isblack == 1) {
		while (1) {
			Apress(s, mate_data, sk);
		}
		
		Brefresh(s, mate_data, sk);
		Sleep(100000);
	}
	else {
		while (1) {
			Apress(s, mate_data, sk);
		}

		Brefresh(s, mate_data, sk);
		Sleep(100000);
	}
}

struct userData waitMatch(SOCKET sk) {

	char* buf[sizeof(struct userData)];
	struct userData ud = {.length = -1};
	int reval; 

	reval = recvData(sk, buf, sizeof(struct userData));

	if (reval > 0) {

		memcpy(&ud, buf, sizeof(struct userData));

		ud.ID[ud.length] = '\0';
	}

	if (ud.length == -1) {
		printf("Server斷線，無法配對，正在關閉程式...");
		ps();
		exit(-1);
	}
	else {
		printf("配對成功，收到對戰者資訊...\n");
		printf("對手名子: %s\n", ud.ID);
		printf("對手PORT: %d\n", ntohs(ud.addr.sin_port));
	

	}

	return ud;
}