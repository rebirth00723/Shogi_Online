#ifndef SHOGI_H
#define SHOGI_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "piece.h"		
#pragma warning (disable:4996)


typedef struct _tagShogi{

	POS pos_b[16];//[16]:´Ñ¤l [2]:®y¼Ð
	POS pos_r[16];
	int  isblack;
	void(*print)(struct _tagShogi);

} shogi;

shogi initShogi(int isblack);

int offset(int pos);

void print(shogi);






#endif // !SHOGI_H


