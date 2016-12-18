#define ID_SIZE 15
#include <winsock.h>

struct playerData {

	char ID[ID_SIZE];
	SOCKET sk;
	struct sockaddr_in addr;

};

void addPlayer(struct playerData *, struct playerData);
void clrPlayer(struct playerData *);
int playerAmount(struct playerData *);

