#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#define Maxchildnum 3
char file_name[]="/home/lbz/20190425/Steam.exe";
typedef struct {
	pid_t pid;
	int fd;
	short busy;
}process_data;

typedef struct 
{
    //int data_len;
    long data_len;
    char buf[100];
}train;
