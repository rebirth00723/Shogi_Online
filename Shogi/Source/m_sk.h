#define BUF_SIZE 512
#define boolean int
#define true 1
#define false 0
#define ps() system("pause")
#define cls() system("cls")

#pragma warning(disable: 4996)
#pragma comment (lib, "wsock32.lib")

struct userData {

	struct sockaddr_in addr;
	char* ID[ID_SIZE];

};

int acceptConnect(SOCKET listen, SOCKET* connect,  struct sockaddr_in* conn_addr);
int bindsocket(SOCKET, struct sockaddr_in *);
int checkError(int, char*);
void createAddr(struct sockaddr_in*, char*, int);
void createAddrA(struct sockaddr_in*, int);
int createServer(SOCKET sk, int port, int backlog);
int connectServer(SOCKET, struct sockaddr_in, int);
void getDataList(char* list, char* str);
void getsocket(SOCKET *sk);
int hasData(char*);
int listensocket(SOCKET, int);
int recvData(SOCKET sk, char* buf, int len);
