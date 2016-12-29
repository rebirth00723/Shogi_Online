#define ID_SIZE 120
#include <winsock.h>
#include <stdbool.h>

#ifndef PLAYER_H
#define PLAYER_H
struct playerData {

	char ID[ID_SIZE];
	SOCKET sk;
	struct sockaddr_in addr;

};
struct userData {

	struct sockaddr_in addr;
	char ID[ID_SIZE];
	int length;
	bool isServer;
};
struct playerData * addPlayer(struct playerData *, struct playerData);
void clrPlayer(struct playerData *);
int playerAmount(struct playerData *);




#endif // !PLAYER_H


