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

char getPiece_b(int);
char getPiece_r(int);
void getPiece_pos_b(POS*);
void getPiece_pos_r(POS*);
void getPiece_board_default(char**);
void getPiece_board_empty(char**);
#endif