

#include "main.h"
#include "network.h"

int main(int argc, char *args[]){

	if (argc <= 1)
	{
		printHelp();
		return 1;
	}
	
	int port = 10001;
	char cmd[1024];
	memset(cmd, 0, 1024);
	int cmdType = 0;
	char name[30];
	memset(name, 0, 30);

	for (int i = 1; i < argc; i++)
	{
		if (!(strcmp(args[i], "-p")&&strcmp(args[i], "port")))
		{
			if (i+2 <= argc)
			{
				port = getport(args[i+1]);
				if (port <0)
				{
					printError("wrong port input");
					return 2;
				}
			}
		}
		else if (!(strcmp(args[i], "-c") && strcmp(args[i], "credible")))
		{
			if (cmdType) continue;
			
			strcpy(cmd, CMD_GET_CREDIBLE_USERS);
			cmdType = CMD_TYPE_GET_CREDIBLE;
		}
		else if (!(strcmp(args[i], "-s") && strcmp(args[i], "send")))
		{
			if (cmdType) continue;
			if (i+2 <= argc)
			{
				strcpy(cmd, CMD_SEND_FILE);
				strcat(cmd, args[i+1]);
				cmdType = CMD_TYPE_SEND_FILE;
				if (strlen(name))
				{
					strcat(cmd, "|");
					strcat(cmd, name);
				}
				
			}
		}
		else if (!(strcmp(args[i], "-n") && strcmp(args[i], "name")))
		{
			if (i+2 <= argc)
			{
				if (cmdType && cmdType == CMD_TYPE_SEND_FILE)
				{
					strcat(cmd, "|");
					strcat(cmd, args[i+1]);
				}
				else
				{
					strcpy(name, args[i+1]);
				}				
			}
		}
		
		else if (!(strcmp(args[i], "-o") && strcmp(args[i], "online")))
		{
			if (cmdType) continue;
			strcpy(cmd, CMD_GET_ONLINE_USERS);
			cmdType = CMD_TYPE_GET_ONLINE;
		}
	}

	if (!cmdType)
	{
		printError("please input cmd");
		printHelp();
		return 3;
	}
	
	int s = createSocket(port);
	sendCmd(s, cmd);
	char buf[1024];
	memset(buf, 0, 1024);
	recv(s, buf, 1023, 0);	

	switch (cmdType)
	{
	case CMD_TYPE_GET_CREDIBLE:
		for(int i = 0; i<strlen(buf); i++){
			if (buf[i] == '|')
			{
				cout<<'\n';
				continue;
			}
			cout<<buf[i];
		}
		break;
	case CMD_TYPE_GET_ONLINE:
		for(int i = 0; i<strlen(buf); i++){
			if (buf[i] == '|')
			{
				cout<<'\n';
				continue;
			}
			cout<<buf[i];
		}
		break;
	case CMD_TYPE_SEND_FILE:

		break;
	default:
		break;
	}

	close(s);

	return 0;
}

void printError(const char msg[]){
	cout << msg << endl;
}

void printHelp(){
	cout << "please input correctly." <<endl;
	cout << "\t-p/ port : to set port, default is 10001"<<endl;
	cout << "\t-s/ send : to send file, must followed with file path."<<endl;
	cout << "\t-n/ name : to set device name you want to send file to."<<endl; 
	cout << "\t-c/ credible : to get credible users list"<<endl;
	cout << "\t-o/ online : to get online users"<<endl;
}

int getport(const char s[]){
	int x = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] <'0' || s[i] >'9'){
			return -1;
		} else {
			x = x*10 + s[i]-'0';
		}
	}
	return x;
}