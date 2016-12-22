#include <stdio.h>
#include <stdbool.h>
#include "piece.h"



typedef struct{

	int pos_b[16][2];
	int pos_r[16][2];
	void(*init)(const bool);
	void(*print)(shogi);

} shogi;

shogi initShogi();

void init(const bool first);

int offset(int pos);

void print(shogi);



