#include "head.h"

int pop_queue(queue_stat * p_queue_stat_0,p_qnode p_qnode_0)
{
    printf("in pop_queue\n");
    if(0==p_queue_stat_0->used_client_num)
        return -1;
    else
    {
        p_queue_stat_0->used_client_num--;
        //*new_fd=p_queue_stat_0->p_queue_head->fd;
        printf("fd is %d,",p_queue_stat_0->p_queue_head->fd);
        printf("command_code is %d,",p_queue_stat_0->p_queue_head->command_code);
        printf("command2 is %s\n",p_queue_stat_0->p_queue_head->command);

        memcpy(p_qnode_0,p_queue_stat_0->p_queue_head,sizeof(qnode));
        p_queue_stat_0->p_queue_head=p_queue_stat_0->p_queue_head->next;
        free(p_queue_stat_0->p_queue_head);
        if(NULL==p_queue_stat_0->p_queue_head)
            p_queue_stat_0->p_queue_tail=NULL;
        return 0;
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

void* pthread_func_execute(void *p)
{
    transed transed0;
    memcpy(&transed0,(transed*) p,sizeof(transed));
    int ret;
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
        qnode qnode0;
        ret=pop_queue(transed0.p_queue_stat_0,&qnode0);//如果弹出成功就传送文件
        pthread_mutex_unlock(transed0.p_lock); 
        if(0==ret)
        {
            printf("pop:used_client_num is %d\n",transed0.p_queue_stat_0->used_client_num);
            printf("begin command\n");
            printf("client_fd is %d,command_code is %d,command2 is %s,transed0.flag is %d\n",qnode0.fd,qnode0.command_code,qnode0.command,transed0.flag);
            if(2==transed0.flag)
            {
                printf("transed0.socket_fd2 is %d\n",transed0.socket_fd2);
                send(transed0.socket_fd2,&qnode0,sizeof(qnode),0);
                printf("i am out\n");
                if(4==qnode0.command_code)
                {
                    printf("client puts\n");
                    client_upload_file(transed0.socket_fd2,qnode0.command,basename(qnode0.command),qnode0.user,qnode0.dir_id);
                }
                else
                {
                    printf("client gets\n");
                    client_download_file(transed0.socket_fd2,qnode0.command,qnode0.user,qnode0.dir_id);
                }
            }
            else if(1==transed0.flag)
            {
                if(4==qnode0.command_code)
                {
                    printf("server puts\n");
                    server_recv_file(qnode0.fd);
                }
                else
                {
                    printf("server gets\n");
                    server_send_file(qnode0.fd);
                }
                //执行完了再继续用epoll监听端口
                struct epoll_event event;
                event.events=EPOLLIN;
                event.data.fd=qnode0.fd;
                epoll_ctl(transed0.epollid,EPOLL_CTL_ADD,qnode0.fd,&event);
            }
        }
    }
}




int server_log_insert(qnode qnode0)
{
    char s1[4298];
    memset(s1,0,sizeof(s1));
    sprintf(s1,"insert into log (user,command1,command2,time) values( '%s','%d','%s', CURRENT_TIMESTAMP )",qnode0.user,qnode0.command_code,qnode0.command); 
    mysql_insert(s1," ");
    return 1;
}











