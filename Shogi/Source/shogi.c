#include "shogi.h"
					 
shogi initShogi() {
	shogi s;

	int *a, *b;

	a = &s.pos_b;
	b = &piece_pos_b;

	for (int i = 0; i < 31; i++) {
		*a = *b;
		++a;
		++b;
	}

	s.print = print;
}


void init(const bool first){



	printf("%d", first);
}

int offset(int pos)
{
	pos = 3 + pos * 2;
	return pos;
}

void print(shogi s) {

	char _board[48][25];
	int x, y;

	strcpy(_board, board_empty);

	for (int i = 0; i < 16; i++) {
		x = s.pos_b[i][0];
		y = s.pos_b[i][1];
		_board[y][x] = piece_b[i];
	}

	for (int i = 0; i < 25; i++)
		printf("%s", _board[i]);
		
	
}