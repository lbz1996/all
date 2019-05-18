#include "head.h"



void time_queue_push(time_queue *p_time_queue,time_node *p_time_node)
{
    if(0==p_time_queue->user_num)
    {
        printf("debug%d\n",__LINE__);
        p_time_queue->time_node_head=p_time_queue->time_node_tail=p_time_node;
        printf("debug%d\n",__LINE__);
    }
    else
    {
        printf("debug%d\n",__LINE__);
        p_time_queue->time_node_tail->next=p_time_node;
        p_time_node->last=p_time_queue->time_node_tail;
        p_time_queue->time_node_tail=p_time_node;
        printf("debug%d\n",__LINE__);
    }
    printf("debug%d\n",__LINE__);
    p_time_node->next=NULL; 
    printf("debug%d\n",__LINE__);
    ++p_time_queue->user_num;//人数设不设置上限啊......
}
//好像不需要pop......
int time_queue_pop(time_queue *p_time_queue,time_node *p_time_node)
{
    if(0<p_time_queue->user_num)
    {
        --p_time_queue;
        p_time_node=p_time_queue->time_node_head;
        p_time_queue->time_node_head=p_time_queue->time_node_head->next;
        return 1;
    }
    else
    {
        return 0;
    }
}

int time_queue_find(time_queue *p_time_queue,int fd,time_node **p_time_node)
{
    time_node *p_time_node_0=p_time_queue->time_node_head;
    while(NULL!=p_time_node_0)
    {
        if(fd==p_time_node_0->fd1)//||fd==p_time_node_0->fd2)
        {
            *p_time_node=p_time_node_0;
            return 1;
        }
        else
        {
            p_time_node_0=p_time_node_0->next;
        }
    }
    return 0;
}


//外部判断user_num,为0的时候不必遍历删除
int time_queue_kill(time_queue *p_time_queue,time_t time_now,int epollid)
{   int ret;
    time_node *p_time_node=p_time_queue->time_node_head;
    while(p_time_node!=NULL)
    {
        if(time_now-p_time_node->last_ask_time>=10)
        {
            printf("client_fd %d will be killed\n",p_time_node->fd1);
            //epoll也应该取消监听...
            struct epoll_event event;
            event.events=EPOLLIN;
            event.data.fd=p_time_node->fd1;
            ret=epoll_ctl(epollid,EPOLL_CTL_DEL,p_time_node->fd1,&event);                    FUNC_ERROR(ret,-1,"epoll_ctl");
            close(p_time_node->fd1);//先取消监听再关闭,直接关闭不管监听可以么?
            --p_time_queue->user_num;
            free(p_time_node);
            if(p_time_node==p_time_queue->time_node_head)
            {
                p_time_queue->time_node_head=p_time_node->next;
                p_time_node=p_time_queue->time_node_head;
                continue;
            }
            if(p_time_node==p_time_queue->time_node_tail)
            {
                p_time_queue->time_node_tail=p_time_node->last;
                break;
            }
        }
        p_time_node=p_time_node->next;
    }
    return 1;
}
