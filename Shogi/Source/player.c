#include "player.h"


void addPlayer(struct playerData* players, struct playerData data) {

	if (strlen(players[0].sk) == -1)
		players[1] = players[0];


	players[0] = data;
}

void clrPlayer(struct playerData*  players) {

	players[0].sk = -1;
	players[0].sk = -1;
}

int playerAmount(struct playerData *players) {

	int a = 0;

	if (strlen(players[0].sk) < 0)
		a++;
	if (strlen(players[1].sk) < 0)
		a++;

	return a;
}
