#ifndef PIECE_H
#define PIECE_H
#include <stdio.h>
#include <string.h>
#define PIECE_AMOUNT 16

typedef struct {

	int x;
	int y;
} POS;

void getPiece(int, char*, int color);
void getPiece_pos(POS*);
char* getPiecer(int, int);
void getPiece_board_default(char**);
void getPiece_board_empty(char[27][52]);
#endif