#ifndef SHOGI_H
#define SHOGI_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "piece.h"		
#pragma warning (disable:4996)


typedef struct _tagShogi{

	POS pos[2][16];//[16]:´Ñs
	int  isblack;
	void(*print)(struct _tagShogi);

} shogi;

shogi initShogi(int isblack);

int offset(int pos);

void print(shogi);






#endif // !SHOGI_H


