#include "shogi.h"	 
shogi initShogi(int isblack) {
	shogi s;


	getPiece_pos_b(s.pos_b);
	getPiece_pos_r(s.pos_r);
	s.isblack = isblack;
	s.print = print;

	return s;
}


int offset(int pos)
{
	pos = 3 + pos * 2;
	return pos;
}

void print(shogi s) {

	char _board[25][48];
	int x, y;
	getPiece_board_empty(_board);

	for (int i = 0; i < 16; i++) {
		x = s.pos_b[i].x;
		y = s.pos_b[i].y;
		_board[x][y] = offset(getPiece_b(i));
	}

	/*for (int i = 0; i < 25; i++)
		printf("%s", _board[i]);/=*/
		
	
}