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
struct sending choose(shogi *s);

void ControlThread(void*);

void Apress(shogi *s, struct userData mate_data, SOCKET sk, char*);
void Brefresh(shogi *s, struct userData mate_data, SOCKET sk);
void buildServer(SOCKET*, int);

void connectMate(SOCKET*, struct userData, int, SOCKET*);
void gotoxy(int, int);
void login(SOCKET*, char*);
void pressPiece(shogi *s, struct userData mate_data, SOCKET sk, SOCKET mate, char*);

struct userData waitMatch(SOCKET);

void test() {

	shogi s = initShogi(0);

	s.print(s);
	system("pause");
}

int main() {


	char ID[ID_SIZE];
	SOCKET sk;
	SOCKET mate;
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


	connectMate(&sk, mate_data, port, &mate);

	Sleep(500);
	cls();

	shogi s = initShogi(mate_data.isServer);


	pressPiece(&s, mate_data, sk, mate, ID);

	system("pause");
	
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


struct sending choose(shogi *s)
{
	HANDLE handle;
	DWORD cnt;//儲存出入
	DWORD mode;//Console Mode
	INPUT_RECORD input;
	int x = 0, y = 9;
	int id;
	int isSelect = 0;
	struct sending S;
	handle = GetStdHandle(STD_INPUT_HANDLE);//先取得基本輸入Handle
	GetConsoleMode(handle, &mode);//得到基本輸入的Mode
	SetConsoleMode(handle, mode & ~ENABLE_LINE_INPUT);//設定基本輸入模式，其中~ENABLE_LINE_INPUT代表不用按下Enter也可動作
	
	gotoxy(0, 9);//預計設定好案件

	while (ReadConsoleInput(handle, &input, 1, &cnt))//開始讀取使用者的動作
	{
		if (input.EventType == KEY_EVENT)
		{
			if (input.Event.KeyEvent.bKeyDown == TRUE)
			{
				
				if (input.Event.KeyEvent.wVirtualKeyCode == VK_SPACE)//space
					if (isSelect == 0) {
						
						for (int i = 0; i < PIECE_AMOUNT; i++) {
							
							if (s->pos[1][i].x == y && s->pos[1][i].y == x) {
								isSelect = 1;
								id = i;
								cls();
								s->print(*s);
								char* c = getPiecer(i, s->isblack);
								printf("你選擇了 [ %c%c ]!!!\n", c[0], c[1]);
								break;
							}
						}
						if (!isSelect) {
							cls();
							s->print(*s);
							printf("選擇錯誤...請重新選擇!!!\n");
							continue;
						}
					}
					else {
						int val;
						val = move(s, id, y, x, &S);
						if (!val) {
							cls();
							s->print(*s);
							printf("移動失敗...請重新移動!!!\n");
							continue;
						}
						else {
							return S;
							
						}
							
					}

				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
					if (isSelect) {
						isSelect = 0;
						cls();
						s->print(*s);
						printf("重新選擇棋子!!!\n");
					}
				}
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) {//left
					x--;
					if (x < 0) x = 0;
						
				}
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) {
					x++;
					if (x > 8) x = 8;
				}//right
					
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_UP) {//up
					y--;
					if (y < 0) y = 0;
				}
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {//down
					y++;
					if (y > 9) y = 9;
				}
				gotoxy(x, y);
	
			}
		}
	}
	return S;
}

void ControlThread(void *param) {

}


void Apress(shogi *s, struct userData mate_data, SOCKET sk, char* ID)
{
	int reval;
	struct sending S;

	cls();
	s->print(*s);
	printf("請下棋\n");

	S = choose(s);

	char buf[sizeof(struct sending)];

	memcpy(buf, &S, sizeof(S));
	reval = send(sk, buf, sizeof(buf), 0);
	reval = WSAGetLastError();
}

void Brefresh(shogi *s, struct userData mate_data, SOCKET sk)
{
	cls();
	s->print(*s);

	printf("耐心點，等待對手[%s]下棋...\n", mate_data.ID);
	struct sending S;
	int reval;
	char buf[sizeof(struct sending)];
	reval = recvData(sk, buf, sizeof(struct sending));

	if (reval > 0) {

		memcpy(&S, buf, sizeof(struct sending));

		s->pos[0][S.id].x = S.move.x;
		s->pos[0][S.id].y = S.move.y;

		s->pos[1][S.dead].x = -1;
		s->pos[1][S.dead].y = -1;
	}

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

void connectMate(SOCKET* sk, struct userData mate_data, int port, SOCKET* mate)
{
	struct sockaddr_in mate_addr;
	int reval;

	if (mate_data.isServer) {
	

		buildServer(sk , port);

		reval =	acceptConnect(*sk, mate, &mate_addr);


	}
	else{

		reval = connectServer(*sk, mate_data.addr);
		mate = -1;
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
	
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = offset(xpos)*2; scrn.Y = offset(ypos);
	SetConsoleCursorPosition(hOuput, scrn);
} //接著輸入這個函式,這樣就可以在其他函式使用了


void login(SOCKET *sk, char* ID) {

	struct sockaddr_in addr;

	//char* ip;
	char ip[20];
	int port;
	int reval;

	printf("設定一個響亮的稱呼來震懾敵手吧!\n");
	printf("你的稱呼:");

	scanf("%s", ID);
	//strcpy(ID, "456");


	//cls();

	printf("真是個不錯的稱呼 %s\n", ID);

	printf("請問現在要進入到哪一個伺服器進入配對?\n");

	while (1) {


		printf("IP:");
		
		scanf("%s", ip);
		//ip = "127.0.0.1";

		printf("Port:");

		scanf("%d", &port);
		//port = 123;

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

void pressPiece(shogi *s, struct userData mate_data, SOCKET sk, SOCKET mate, char* ID)
{
	while (1) {
		if (s->isblack == 1) {
			Apress(s, mate_data, mate, ID);
			if (s->pos[0][0].x == -1) {
				cls();
				s->print(*s);
				printf("恭喜[%s]，你贏了!!", ID);
				return;
			}
			else if (s->pos[1][0].x == -1) {
				cls();
				s->print(*s);
				printf("你輸給了[%s]，再接再厲!!", mate_data.ID);
				return;
			}
				
			Brefresh(s, mate_data, mate);
		}
		else {

			Brefresh(s, mate_data, sk);
			if (s->pos[0][0].x == -1) {
				cls();
				s->print(*s);
				printf("恭喜[%s]，你贏了!!", ID);
				return;
			}
			else if (s->pos[1][0].x == -1) {
				cls();
				s->print(*s);
				printf("你輸給了[%s]，再接再厲!!", mate_data.ID);
				return;
			}
			Apress(s, mate_data, sk, ID);
		}
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
		printf("三秒後開始棋局");
		Sleep(2900);

	}

	return ud;
}