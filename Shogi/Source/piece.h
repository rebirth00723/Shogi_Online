#ifndef PIECE_H
#define PIECE_H
#include <stdio.h>
#include <string.h>
#define offset_x 3
#define offset_y 3

typedef struct {

	int x;
	int y;
} POS;

void getPiece(int, char*, int color);
void getPiece_pos(POS*);
void getPiece_board_default(char**);
void getPiece_board_empty(char[27][52]);
#endif