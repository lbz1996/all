#include "head.h"
#include "sql_func.c"
#include "pthread_func.c"
#include "file_func.c"
#include "user_func.c"
#include "kill_time.c"
int main()
{
    int ret;
    printf("Hello world\n"); 
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);           FUNC_ERROR(socket_fd,-1,"socke");
    int reuse=1;                                                                                                                                  
    ret=setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int)); FUNC_ERROR(socket_fd,-1,"setsockopt");        

    struct sockaddr_in sockaddr_in_0;                      bzero(&sockaddr_in_0,sizeof(struct sockaddr_in));
    sockaddr_in_0.sin_family=AF_INET;
    sockaddr_in_0.sin_port=htons(1234);
    sockaddr_in_0.sin_addr.s_addr=INADDR_ANY;//=inet_addr("0.0.0.0"),设置的是本机的服务器地址....?
    int sockaddr_len=sizeof(struct sockaddr);
    ret=bind(socket_fd,(struct sockaddr*) &sockaddr_in_0,sockaddr_len);   FUNC_ERROR(ret,-1,"bind");
    ret=listen(socket_fd,MAX_CLIENT_NUM);                                 FUNC_ERROR(ret,-1,"listen");

    transed transed0;                                                                                                                           
    pthread_mutex_t lock;
    ret=pthread_mutex_init(&lock, NULL);         if(0!=ret){printf("pthread_mutex_init is wrong\n");return -1;}
    transed0.p_lock=&lock;
    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);
    transed0.p_cond=&cond;

    //先搭epoll
    int epollid=epoll_create(1);                                              FUNC_ERROR(epollid,-1,"epoll_create");                                                                                                                  
    transed0.epollid=epollid;
    struct epoll_event     event,eventarg[MAX_CLIENT_NUM];

    event.events=EPOLLIN;
    event.data.fd=socket_fd;
    ret=epoll_ctl(epollid,EPOLL_CTL_ADD,socket_fd,&event);                    FUNC_ERROR(ret,-1,"epoll_ctl");

    time_queue time_queue_0;
    memset(&time_queue_0,0,sizeof(time_queue));

    //建立多线程
    queue_stat queue_stat_0;                      memset(&queue_stat_0,0,sizeof(queue_stat));
    transed0.p_queue_stat_0=&queue_stat_0;
    pthread_t pthread_id_array[MAX_PTHREAD_NUM];  memset(&pthread_id_array,0,sizeof(pthread_id_array));
    transed0.flag=1;
    //ret=pthread_create(&pthread_id,NULL,pthread_func_execute,(void *) &transed0);                    if(0!=ret){printf("pthread_create wrong\n");return -1;}
    for(int i=0;i<MAX_PTHREAD_NUM;++i)
    {
        pthread_t pthread_id;
        ret=pthread_create(&pthread_id,NULL,pthread_func_execute,(void *) &transed0);                if(0!=ret){printf("pthread_create wrong\n");return -1;}
    }




    int readynum; 
    while(1)
    { 
        memset(eventarg,0,sizeof(eventarg));
        readynum=epoll_wait(epollid,eventarg,MAX_CLIENT_NUM+1,0);
        for(int i=0;i<readynum;++i)
        {
            if(socket_fd==eventarg[i].data.fd)
            {
                int new_fd;         
                new_fd=accept(socket_fd,(struct sockaddr*) &sockaddr_in_0,&sockaddr_len);     FUNC_ERROR(ret,-1,"accept");                                 printf("new_fd is %d\n",new_fd);
                int is_main;
                recv(new_fd,&is_main,sizeof(int),0);
                printf("%d:new_fd is %d,is_main is %d\n",__LINE__,new_fd,is_main);
                if(is_main)
                {   printf("debug%d\n",__LINE__);
                    time_node *time_node_new = (time_node *) malloc(sizeof(time_node));          
                    time_node_new->fd1=new_fd;
                    time_node_new->last_ask_time=time(NULL);
                    printf("debug%d\n",__LINE__);
                    time_queue_push(&time_queue_0,time_node_new);
                    printf("debug%d\n",__LINE__);
                }
                event.data.fd=new_fd;
                epoll_ctl(epollid,EPOLL_CTL_ADD,new_fd,&event);
            }
            else
            {
                time_node *update_time_node;
                if(1==time_queue_find(&time_queue_0,eventarg[i].data.fd,&update_time_node)) 
                    update_time_node->last_ask_time=time(NULL);  
                qnode qnode_0;
                ret=recv(eventarg[i].data.fd,&qnode_0,sizeof(qnode),0);
                //printf("in %d ,ret is %d\n",__LINE__,ret);
                qnode_0.fd=eventarg[i].data.fd;//收包之后把对应的fd修改加入
                //printf("in server%d: ",__LINE__);
                printf("fd is %d,command_code is %d,command2 is %s\n",qnode_0.fd,qnode_0.command_code,qnode_0.command);
                int command_code=qnode_0.command_code;
                if(0==ret)
                {
                    printf("client_fd %d 断开\n",eventarg[i].data.fd);
                    event.data.fd=eventarg[i].data.fd;
                    epoll_ctl(epollid,EPOLL_CTL_DEL,eventarg[i].data.fd,&event);
                }
                else
                {
                    printf("in %d:command_code is %d\n",__LINE__,command_code);
                    if(0==command_code)
                    {
                        printf("recv 00000\n");
                    }
                    else if(4!=command_code&&5!=command_code)//命令不是puts或gets就主线程自己做
                    {
                        printf("in %d\n",__LINE__);
                        switch (command_code)
                        {
                        case 1:verify_login(eventarg[i].data.fd,&qnode_0);break;
                        case 2:server_cd(eventarg[i].data.fd);break;
                        case 3:server_ls(eventarg[i].data.fd);break;
                        case 6:server_remove(eventarg[i].data.fd);break;
                        case 7:server_pwd(eventarg[i].data.fd);break;
                        case 8:server_mkdir(eventarg[i].data.fd);break;
                        }
                    }
                    else
                    {
                        p_qnode p_qnode_0=(p_qnode) calloc(1,sizeof(qnode)); 
                        memcpy(p_qnode_0,&qnode_0,sizeof(qnode));
                        printf("in %d\n",__LINE__);
                        //!!!!!!!执行时取消对应端口的监听,执行完了再加回来(自己回取消的好像记得加回来...->EPOLLONSHOT.....)
                        event.data.fd=eventarg[i].data.fd;
                        epoll_ctl(epollid,EPOLL_CTL_DEL,eventarg[i].data.fd,&event);
                        //加锁
                        pthread_mutex_lock(&lock);                                                                                                              
                        queue_insert(p_qnode_0,&queue_stat_0);
                        pthread_mutex_unlock(&lock);
                        pthread_cond_signal(&cond);
                    }
                    server_log_insert(qnode_0);
                }
            }
        }
        if(0<time_queue_0.user_num)
        {
            time_queue_kill(&time_queue_0,time(NULL),epollid);

        }
    }
    return 0;
}

