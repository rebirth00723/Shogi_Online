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
int		checkNoPiece(shogi s, POS pos);
shogi	initShogi(int isblack);

void	kill(shogi* s, POS pos);

int		move(shogi* s, int id, int x, int y);

int		offset(int pos);

void	print(shogi);

void	showSurvive(shogi);

//success: 1
int gerneral	(shogi s, POS pos, POS pos2);
int knight		(shogi s, POS pos, POS pos2);
int elephant	(shogi s, POS pos, POS pos2);
int car			(shogi s, POS pos, POS pos2);
int horse		(shogi s, POS pos, POS pos2);
int soldier		(shogi s, POS pos, POS pos2);
int cannon		(shogi s, POS pos, POS pos2);

int noObstacle(shogi s, POS pos, POS pos2);
#endif // !SHOGI_H


