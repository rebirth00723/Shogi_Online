#include "player.h"


struct playerData * addPlayer(struct playerData* players, struct playerData data) {

	if (strlen(players[0].sk) == -1) {
		players[0] = data;
		return &players[0];
	}
		
	else {
		players[1] = data;
		return &players[1];
	}
	

}

void clrPlayer(struct playerData*  players) {

	players[0].sk = -1;
	players[1].sk = -1;
}

int playerAmount(struct playerData *players) {

	int a = 0;

	if (strlen(players[0].sk) < 0)
		a++;
	if (strlen(players[1].sk) < 0)
		a++;

	return a;
}
