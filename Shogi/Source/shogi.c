#include "shogi.h"	
#include "math.h"
shogi initShogi(int isblack) {
	shogi s;

	s.isblack = isblack;

	getPiece_pos(s.pos[0]);
	getPiece_pos(s.pos[1]);

	s.print = print;
	s.showSurvive = showSurvive;
	s.move = move;
	return s;
}

int  move(shogi* s, int id, int x, int y)
{
	POS pos = s->pos[1][id];
	POS pos2 = { x, y };
	int val = 0;

	if (id == 0)
		val = gerneral(*s, pos, x, y);
	else if (id < 3)
		val = knight(*s, pos, x, y);
	else if (id < 5)
		val = elephant(*s, pos, x, y);
	else if (id < 7)
		val = car(*s, pos, x, y);
	else if (id < 9)
		val = horse(*s, pos, x, y);
	else if (id < 11)
		val = cannon(*s, pos, x, y);
	else
		val = soldier(*s, pos, x, y);

	if (val == 1) 
		s->pos[1][id] = pos2;
	
	
	return val;
}


int offset(int pos)
{
	pos = 4 + pos * 2;
	return pos;
}

void print(shogi s) {

	char _board[27][52], str[2];
	int X, x, Y, y;
	getPiece_board_empty(_board);

	for (int i = 0; i < 16; i++) {
	
		X = offset(s.pos[1][i].x);
		Y = offset(s.pos[1][i].y) * 2;
		x = offset(9 - s.pos[0][i].x);
		y = offset(s.pos[0][i].y) * 2;
	

		getPiece(i, str, s.isblack);


		_board[X][Y] = str[0];
		_board[X][Y + 1] = str[1];

		getPiece(i, str, ! s.isblack);

		_board[x][y] = str[0];
		_board[x][y + 1] = str[1];
	}

	for (int i = 0; i < sizeof(_board) / (sizeof(*_board)); i++)
		printf("%s", _board[i]);
		
	
}

void showSurvive(shogi s)
{
	int i = 0;
	for (; i < 3; i++) {
	
		if (s.pos[1][i].x != -1) {
			char piece[2] = {0};
			getPiece(i, piece, s.isblack);
			printf("%d: %c%c(%c,%d)¡@", i, piece[0], piece[1],  'A' + s.pos[1][i].x, s.pos[1][i].y);
		}
	}

	printf("\n");

	for (; i < 11; i++) {

		if (s.pos[1][i].x != -1) {
			char piece[2] = { 0 };
			getPiece(i, piece, s.isblack);
			printf("%d: %c%c(%c,%d)¡@", i, piece[0], piece[1], 'A' + s.pos[1][i].x, s.pos[1][i].y);
		}
	}

	printf("\n");

	for (; i < 16; i++) {

		if (s.pos[1][i].x != -1) {
			char piece[2] = { 0 };
			getPiece(i, piece, s.isblack);
			printf("%d: %c%c(%c,%d)¡@", i, piece[0], piece[1], 'A' + s.pos[1][i].x, s.pos[1][i].y);
		}
	}
	printf("\n");
}

int gerneral(shogi s, POS pos, int x, int y)
{
	if (y < 3 || y>5 || x > 9 || x < 7)
		return 0;
	else {
		if (abs(pos.x - x) == 1 && pos.y == y)
			return 1;
		if (abs(pos.y - y) == 1 && pos.x == x)
			return 1;
	}
	return 0;
}

int knight(shogi s, POS pos, int x, int y)
{
	return 0;
}

int elephant(shogi s, POS pos, int x, int y)
{
	return 0;
}

int car(shogi s, POS pos, int x, int y)
{
	return 0;
}

int horse(shogi s, POS pos, int x, int y)
{
	return 0;
}

int soldier(shogi s, POS pos, int x, int y)
{
	return 0;
}

int cannon(shogi s, POS pos, int x, int y)
{
	return 0;
}
