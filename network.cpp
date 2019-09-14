#include "network.h"

int createSocket(int port){
	int sock;
	struct sockaddr_in serAddr;

	serAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0)
	{
		return -1;
	}

	if (connect(sock, (struct sockaddr*)&serAddr, sizeof(serAddr)))
	{
		return 12;
	}

	return sock;
}

int sendCmd(int sock, const char *str){
	
	char buf[1024];
	memset(buf, 0, 1024);

	strcpy(buf, str);
	send(sock, buf, sizeof(buf), 0);

	return 0;
}