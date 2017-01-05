#include "shogi.h"	 
shogi initShogi(int isblack) {
	shogi s;


	
	s.isblack = isblack;

	getPiece_pos(s.pos[0]);
	getPiece_pos(s.pos[1]);

	s.print = print;

	return s;
}


int offset(int pos)
{
	pos = 3 + pos * 2;
	return pos;
}

void print(shogi s) {

	char _board[25][48], str[2];
	int X, x, Y, y;
	getPiece_board_empty(_board);

	for (int i = 0; i < 16; i++) {
	
		X = offset(s.pos[0][i].x);
		Y = offset(s.pos[0][i].y) * 2;
		x = offset(9 - s.pos[1][i].x);
		y = offset(s.pos[1][i].y) * 2;
	
		if(s.isblack == 1)
			getPiece(i, str, 1);
		else
			getPiece(i, str, 0);

		_board[X][Y] = str[0];
		_board[X][Y + 1] = str[1];

		if (s.isblack == 1)
			getPiece(i, str, 0);
		else
			getPiece(i, str, 1);

		_board[x][y] = str[0];
		_board[x][y + 1] = str[1];
	}

	for (int i = 0; i < 25; i++)
		printf("%s", _board[i]);
		
	
}