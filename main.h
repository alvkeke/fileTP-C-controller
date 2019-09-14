
#include <iostream>

using namespace std;

const char CMD_GET_ONLINE_USERS[] =      "_GET_ONLINE_USERS_LIST________";
const char CMD_SEND_FILE[] =             "_SEND_FILE_TO_________________";
const char CMD_GET_CREDIBLE_USERS[] =    "_GET_CREDIBLE_USERS_LIST______";

const int CMD_TYPE_GET_ONLINE = 1;
const int CMD_TYPE_GET_CREDIBLE = 2;
const int CMD_TYPE_SEND_FILE = 3;

void printError(const char msg[]);

void printHelp();

int getport(const char s[]);