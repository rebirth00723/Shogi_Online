#include <stdio.h>
#include <stdbool.h>

typedef struct shogi{

	void(*print)(const bool);
} shogi;


void init(const bool first);
void initShogi(shogi* s);



void initShogi(shogi *s) {

	s->print = init;
}