
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>


int createSocket(int port);
int sendCmd(int sock, const char *str);