#include "head.h"
#include "trans_file.c"
#include "send_receive.c"
#include "make_child.c"

int main()
{
    int ret;
    process_data *array=(process_data*)calloc(Maxchildnum,sizeof(process_data));

    make_child(array,Maxchildnum);
    for(int i=0;i<Maxchildnum;++i)
        printf("%3d",array[i].fd);
    int socket_id=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socket_id)
    {
        perror("socket");
        return -1;
    }
    printf("my socket_id is %d\n",socket_id);

    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_port=htons((short) 1234);//端口记得要转换......
    sockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    unsigned int sockaddr_length=sizeof(sockaddr);
    ret=bind(socket_id,(struct sockaddr*) &sockaddr,sockaddr_length);
    if(-1==ret)
    {
        perror("bind");
        return -1;
    }
    ret=listen(socket_id,10);
    if(-1==ret)
    {
        perror("listen");
        return -1;
    }



    int epoll_id=epoll_create(11);
    struct epoll_event epoll_event,*evs;
    evs=(struct epoll_event*)calloc(Maxchildnum+1,sizeof(struct epoll_event));
    epoll_event.events=EPOLLIN;
    epoll_event.data.fd=socket_id;
    ret=epoll_ctl(epoll_id,EPOLL_CTL_ADD,socket_id,&epoll_event);
    if(-1==ret)
    {
        perror("epoll_ctl");
        return -1;
    }
    for(int i=0;i<Maxchildnum;i++)
    {
        epoll_event.data.fd=array[i].fd;
        ret=epoll_ctl(epoll_id,EPOLL_CTL_ADD,array[i].fd,&epoll_event);
        if(-1==ret)
        {
            printf("%d,",i);
            perror("epoll_ctl");
            return -1;
        }
        printf("%d\n",array[i].fd);
    }



    int linked_fd,ready_num;
    while(1)
    {
        ready_num=epoll_wait(epoll_id,evs,Maxchildnum+1,-1);
        printf("ready_num is %d\n",ready_num);
        if(-1==ready_num)
        {
            perror("epoll_wait");
            return -1;
        }
        for(int i=0;i<ready_num;++i)
        {
            printf("ready events is %d ,fd is %d\n",evs[i].events,evs[i].data.fd);
            if(evs[i].events==EPOLLIN&&evs[i].data.fd==socket_id)
            {
                linked_fd=accept(socket_id,NULL,NULL);
                for(int j=0;j<Maxchildnum;++j)
                {
                    if(0==array[j].busy)
                    {
                        array[j].busy=1;
                        //通知子进程干活
                        sendfd(array[j].fd,linked_fd);
                        printf("%d child will be busy\n",array[j].pid);
                        break;
                    }
                }
                close(linked_fd);
            }
            for(int j=0;j<Maxchildnum;++j)
            {
                if(evs[i].data.fd==array[j].fd)
                {
                    int temp;
                    read(array[j].fd,&temp,1);
                    array[j].busy=0;
                    printf("%d child is not busy\n",array[j].pid);
                }
            }	
        }
    }
    return 0;
}
