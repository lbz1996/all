#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>                                                                                                                       

#include<unistd.h>
#include<sys/epoll.h>
#include<sys/stat.h>
#include<fcntl.h>

#define MAX_PTHREAD_NUM 10
#define MAX_CLIENT_NUM 10
char file_name[]="/home/lbz/20190425/Steam.exe"; 
#define FUNC_ERROR(ret,retval,func)\
{if(ret==retval)\
{printf("%d line-",__LINE__);\
perror(func);return -1;}}

typedef struct qnode
{
    int fd;
    struct qnode *next;
}qnode,*p_qnode;

typedef struct queue_stat
{
    p_qnode p_queue_head,p_queue_tail;
    int used_pthread_num;
    int used_client_num;
}queue_stat;

typedef struct transed
{
    queue_stat *p_queue_stat_0;
    pthread_mutex_t *p_lock;
    pthread_cond_t  *p_cond;
}transed;

typedef struct{
    long data_len;
    char buf[1000];
                    
}train;

#include "trans_file.c"



void* pthread_func(void *p);
int queue_insert(p_qnode p_qnode_0,queue_stat *p_queue_stat_0);













