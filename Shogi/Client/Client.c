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
	printf("�s�����A����...\n");
	reval = connectServer(sk, addr);
	send(sk, ID, strlen(ID), 0);
	

	while (1) {
	
		Sleep(100);
	}*/
}


int choose()
{
	HANDLE handle;
	DWORD cnt;//�x�s�X�J
	DWORD mode;//Console Mode
	INPUT_RECORD input;
	int x = 0, y = 0;
	POS start = { -1,-1 };
	POS end = { -1,-1 };
	handle = GetStdHandle(STD_INPUT_HANDLE);//�����o�򥻿�JHandle
	GetConsoleMode(handle, &mode);//�o��򥻿�J��Mode
	SetConsoleMode(handle, mode & ~ENABLE_LINE_INPUT);//�]�w�򥻿�J�Ҧ��A�䤤~ENABLE_LINE_INPUT�N���Ϋ��UEnter�]�i�ʧ@

	gotoxy(0, 0);//�w�p�]�w�n�ץ�

	while (ReadConsoleInput(handle, &input, 1, &cnt))//�}�lŪ���ϥΪ̪��ʧ@
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
	printf("\n�ФU��\n\n");

	

	while (lock) {
		choose();

		
		/*
		s->showSurvive(*s);
		printf("\n��J�Ѥl�s��:");
		scanf("%d", &id);
		getchar();
		if (id < 0 || id >16) {
			cls();
			s->print(*s);
			printf("\n��J���~, ���s��J...\n");
			continue;
		}

		if (s->pos[1][id].x == -1) {
			cls();
			s->print(*s);
			printf("\n�ӴѤl�w�}�`, ���s��J...\n");
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

			printf("\n�z�ثe��ܪ��Ѥl %c%c(%c,%d) \n", piece[0], piece[1], 'A'  + s->pos[1][id].x, s->pos[1][id].y);
			printf("��J���ʮy�� ex: J 6 (���s��ܿ�J 0 0):");
			scanf("%c %d", &x, &y);
			getchar();
			if ( x == '0' && y == 0) {
				cls();
				s->print(*s);
				printf("\n���s��ܴѤl\n\n");
				lock = 1;
				break;
			}
			if (x < 'A' || x> 'J' || y < 0 || y>9) {
				cls();
				s->print(*s);
				printf("\n��J���~�A���s��J...\n");
				continue;
			}

			val = s->move(s, id, x-'A', y);

			if (val == 0) {
				cls();
				s->print(*s);
				printf("\n���ʥ��ѡA���s����...\n");
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
	printf("���ݹ��U��\n");



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
	
		printf("�s����⥢�ѡA�L�k�i����...\n");
	}
	else {
	
		printf("�}�l���...\n");
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
} //���ۿ�J�o�Ө禡,�o�˴N�i�H�b��L�禡�ϥΤF


void login(SOCKET *sk, char* ID) {

	struct sockaddr_in addr;

	char* ip;
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
		ip = "127.0.0.1";

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
		printf("Server�_�u�A�L�k�t��A���b�����{��...");
		ps();
		exit(-1);
	}
	else {
		printf("�t�令�\�A�����Ԫ̸�T...\n");
		printf("���W�l: %s\n", ud.ID);
		printf("���PORT: %d\n", ntohs(ud.addr.sin_port));
	

	}

	return ud;
}