#ifndef __FUNC_H__
#define __FUNC_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <sys/msg.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define ARG_ERROR(argc,n) {if(argc!=n) \
        {printf("wrong argc");return -1;}}
#define FUNC_ERROR(ret,retval,func) {if(ret==retval) \
        {perror(func); return -1;}}
#define DIM(x) sizeof(x) / sizeof(x[0])
#define SWAP(x, y) x = (y + x) - (y = x)
#define RAND() (srand(time(NULL)), rand())
        
typedef struct train
{
    int player;
    int buf[20];
    int res;
}Train;

int get_card_point(int num);
void show_hand_cards(int *buf,int length);

























#endif
