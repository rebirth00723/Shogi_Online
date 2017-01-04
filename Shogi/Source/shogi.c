#include "shogi.h"	 
shogi initShogi(int isblack) {
	shogi s;


	
	s.isblack = isblack;

	if (isblack == 1) {
		getPiece_pos(s.pos[1], 1);
		getPiece_pos(s.pos[0], 0);
	}
	else {
		getPiece_pos(s.pos[0], 1);
		getPiece_pos(s.pos[1], 0);
	}
	

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
	int x_b, y_b, x_r, y_r;
	getPiece_board_empty(_board);

	for (int i = 0; i < 16; i++) {
	
		x_b = offset(s.pos[1][i].x);
		y_b = offset(s.pos[1][i].y) * 2;
		x_r = offset(s.pos[0][i].x);
		y_r = offset(s.pos[0][i].y) * 2;
	
		getPiece(i, str, 1);

		_board[x_b][y_b] = str[0];
		_board[x_b][y_b + 1] = str[1];

		getPiece(i, str, 0);
		_board[x_r][y_r] = str[0];
		_board[x_r][y_r + 1] = str[1];
	}

	for (int i = 0; i < 25; i++)
		printf("%s", _board[i]);
		
	
}