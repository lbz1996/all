#include "head.h"

int main()
{
    int ret;
    printf("Hello world\n");
    int socket_fd=socket(AF_INET,SOCK_STREAM,0); 
    FUNC_ERROR(socket_fd,-1,"socket");
    struct sockaddr_in sockaddr_in_0;
    memset(&sockaddr_in_0,0,sizeof(struct sockaddr_in));
    sockaddr_in_0.sin_family=AF_INET;
    sockaddr_in_0.sin_port=htons(1234);
    sockaddr_in_0.sin_addr.s_addr=INADDR_ANY;//=inet_addr("0.0.0.0"),设置的是本机的服务器地址....?
    int sockaddr_len=sizeof(struct sockaddr);
    ret=bind(socket_fd,(struct sockaddr*) &sockaddr_in_0,sockaddr_len);
    FUNC_ERROR(ret,-1,"bind");
    ret=listen(socket_fd,MAX_CLIENT_NUM);
    FUNC_ERROR(ret,-1,"listen");

    transed transed0;
    pthread_mutex_t lock;
    ret=pthread_mutex_init(&lock, NULL);
    if(0!=ret)
    {
        printf("pthread_mutex_init is wrong\n");
        return -1;
    }
    transed0.p_lock=&lock;

    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);
    transed0.p_cond=&cond;
    //建立多线程
    queue_stat queue_stat_0;
    memset(&queue_stat_0,0,sizeof(queue_stat));
    transed0.p_queue_stat_0=&queue_stat_0;
    pthread_t pthread_id_array[MAX_PTHREAD_NUM];
    memset(&pthread_id_array,0,sizeof(pthread_id_array));
    for(int i=0;i<MAX_PTHREAD_NUM;++i)
    {
        pthread_t pthread_id;
        ret=pthread_create(&pthread_id,NULL,pthread_func,(void *) &transed0);
        if(0!=ret)
        {
            printf("pthread_create wrong\n");
            return -1;
        }
    }
    while(1)
    { 
        int new_fd;
        new_fd=accept(socket_fd,(struct sockaddr*) &sockaddr_in_0,&sockaddr_len);
        FUNC_ERROR(ret,-1,"accept");
        printf("new_fd is %d\n",new_fd);
        p_qnode p_qnode_0=(p_qnode) calloc(1,sizeof(qnode)); 
        (*p_qnode_0).fd=new_fd;
        //加锁
        pthread_mutex_lock(&lock);
        queue_insert(p_qnode_0,&queue_stat_0);
        //解锁
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&cond);
    }
    return 0;
}



int pop_queue(queue_stat * p_queue_stat_0,int *new_fd)
{
    if(0==p_queue_stat_0->used_client_num)
        return -1;
    else
    {
        p_queue_stat_0->used_client_num--;
        *new_fd=p_queue_stat_0->p_queue_head->fd;
        p_queue_stat_0->p_queue_head=p_queue_stat_0->p_queue_head->next;
        if(NULL==p_queue_stat_0->p_queue_head)
            p_queue_stat_0->p_queue_tail=NULL;
        return 0;
    }
}
void* pthread_func(void *p)
{
    transed transed0;
    memcpy(&transed0,(transed*) p,sizeof(transed));
    int ret,new_fd;
    while(1)
    {
        pthread_mutex_lock(transed0.p_lock);
        if(0==transed0.p_queue_stat_0->used_client_num)
        {
            // printf("if in\n");
            pthread_cond_wait(transed0.p_cond,transed0.p_lock);
        }
        // printf("ready to pop\n");
        //弹出一个元素
        pthread_mutex_unlock(transed0.p_lock); 
        ret=pop_queue(transed0.p_queue_stat_0,&new_fd);//如果弹出成功就传送文件
        if(0==ret)
        {
            printf("pop:used_client_num is %d\n",transed0.p_queue_stat_0->used_client_num);
            printf("begin trans\n");
            trans_file(new_fd); 
        }
    }
}
int queue_insert(p_qnode p_qnode_0,queue_stat *p_queue_stat_0)
{
    if(MAX_CLIENT_NUM==(*p_queue_stat_0).used_client_num) 
    {
        printf("queue is full\n");
        return -1;
    }
    else
    {
        printf("push:used_client_num is %d\n",(*p_queue_stat_0).used_client_num);
        if(0==(*p_queue_stat_0).used_client_num)
        {
            p_queue_stat_0->p_queue_head=p_qnode_0;
            p_queue_stat_0->p_queue_tail=p_qnode_0;
        }
        else
        {
            p_queue_stat_0->p_queue_tail->next=p_qnode_0;
            p_queue_stat_0->p_queue_tail=p_qnode_0;
        }
        p_queue_stat_0->used_client_num+=1;
        return 0;
    }
}

