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
	printf("�s�����A����...\n");
	reval = connectServer(sk, addr);
	send(sk, ID, strlen(ID), 0);
	

	while (1) {
	
		Sleep(100);
	}*/
}


struct sending choose(shogi *s)
{
	HANDLE handle;
	DWORD cnt;//�x�s�X�J
	DWORD mode;//Console Mode
	INPUT_RECORD input;
	int x = 0, y = 9;
	int id;
	int isSelect = 0;
	struct sending S;
	handle = GetStdHandle(STD_INPUT_HANDLE);//�����o�򥻿�JHandle
	GetConsoleMode(handle, &mode);//�o��򥻿�J��Mode
	SetConsoleMode(handle, mode & ~ENABLE_LINE_INPUT);//�]�w�򥻿�J�Ҧ��A�䤤~ENABLE_LINE_INPUT�N���Ϋ��UEnter�]�i�ʧ@
	
	gotoxy(0, 9);//�w�p�]�w�n�ץ�

	while (ReadConsoleInput(handle, &input, 1, &cnt))//�}�lŪ���ϥΪ̪��ʧ@
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
								printf("�A��ܤF [ %c%c ]!!!\n", c[0], c[1]);
								break;
							}
						}
						if (!isSelect) {
							cls();
							s->print(*s);
							printf("��ܿ��~...�Э��s���!!!\n");
							continue;
						}
					}
					else {
						int val;
						val = move(s, id, y, x, &S);
						if (!val) {
							cls();
							s->print(*s);
							printf("���ʥ���...�Э��s����!!!\n");
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
						printf("���s��ܴѤl!!!\n");
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
	printf("�ФU��\n");

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

	printf("�@���I�A���ݹ��[%s]�U��...\n", mate_data.ID);
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

	printf("�غc���A����...");

	reval = createServer(*sk, port, 1);
	if (reval == -1) {
		printf("����\n");
		ps();
		exit(-1);
	}
	printf("���ݹ��s�J\n");
	

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
	
		printf("�s����⥢�ѡA�L�k�i����...\n");
	}
	else {
	
		printf("�}�l���...\n");
	}



}
void gotoxy(int xpos, int ypos)
{
	
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = offset(xpos)*2; scrn.Y = offset(ypos);
	SetConsoleCursorPosition(hOuput, scrn);
} //���ۿ�J�o�Ө禡,�o�˴N�i�H�b��L�禡�ϥΤF


void login(SOCKET *sk, char* ID) {

	struct sockaddr_in addr;

	//char* ip;
	char ip[20];
	int port;
	int reval;

	printf("�]�w�@���T�G���٩I�Ӿ_��Ĥ�a!\n");
	printf("�A���٩I:");

	scanf("%s", ID);
	//strcpy(ID, "456");


	//cls();

	printf("�u�O�Ӥ������٩I %s\n", ID);

	printf("�аݲ{�b�n�i�J����@�Ӧ��A���i�J�t��?\n");

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

void pressPiece(shogi *s, struct userData mate_data, SOCKET sk, SOCKET mate, char* ID)
{
	while (1) {
		if (s->isblack == 1) {
			Apress(s, mate_data, mate, ID);
			if (s->pos[0][0].x == -1) {
				cls();
				s->print(*s);
				printf("����[%s]�A�AĹ�F!!", ID);
				return;
			}
			else if (s->pos[1][0].x == -1) {
				cls();
				s->print(*s);
				printf("�A�鵹�F[%s]�A�A���A�F!!", mate_data.ID);
				return;
			}
				
			Brefresh(s, mate_data, mate);
		}
		else {

			Brefresh(s, mate_data, sk);
			if (s->pos[0][0].x == -1) {
				cls();
				s->print(*s);
				printf("����[%s]�A�AĹ�F!!", ID);
				return;
			}
			else if (s->pos[1][0].x == -1) {
				cls();
				s->print(*s);
				printf("�A�鵹�F[%s]�A�A���A�F!!", mate_data.ID);
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
		printf("Server�_�u�A�L�k�t��A���b�����{��...");
		ps();
		exit(-1);
	}
	else {
		printf("�t�令�\�A�����Ԫ̸�T...\n");
		printf("���W�l: %s\n", ud.ID);
		printf("���PORT: %d\n", ntohs(ud.addr.sin_port));
		printf("�T���}�l�ѧ�");
		Sleep(2900);

	}

	return ud;
}