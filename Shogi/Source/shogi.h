#ifndef SHOGI_H
#define SHOGI_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "piece.h"		
#pragma warning (disable:4996)


typedef struct _tagShogi{

	POS pos[2][16];//1 : 自己 0 :別人
	int  isblack;
	void	(*print)		(struct _tagShogi);
	void	(*showSurvive)	(struct _tagShogi);
	int		(*move)			(struct _tagShogi*, int, int, int);

} shogi;

shogi initShogi(int isblack);

int move(shogi* s, int id, int x, int y);

int offset(int pos);

void print(shogi);

void showSurvive(shogi);

//success: 1
int gerneral	(shogi s, POS pos, int x, int y);
int knight		(shogi s, POS pos, int x, int y);
int elephant	(shogi s, POS pos, int x, int y);
int car			(shogi s, POS pos, int x, int y);
int horse		(shogi s, POS pos, int x, int y);
int soldier		(shogi s, POS pos, int x, int y);
int cannon		(shogi s, POS pos, int x, int y);
#endif // !SHOGI_H


