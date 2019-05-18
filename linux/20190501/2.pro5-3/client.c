#include "func.h"

int main(int argc,char* argv[])
{
    //连接阶段
    ARG_ERROR(argc,3);
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser;
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    connect(socketFd,(struct sockaddr*)&ser,sizeof(ser));
    printf("connect success\n");
    //发牌阶段
    Train mysocket;
    memset(&mysocket,0,sizeof(Train));
    recv(socketFd,&mysocket,sizeof(Train),0);
    show_hand_cards(mysocket.buf,20);
    int last_player=(mysocket.res-1)%3;
    Train recvsocket;
    while(1)
    {
        memset(&recvsocket,0,sizeof(Train));
        recv(socketFd,&recvsocket,sizeof(Train),0);
        if(0==recvsocket.res)
        {
            printf("player %d win!\n",recvsocket.player);
            break;
        }
        else if()
        {
            
        }
    }
    return 0;
}

int get_card_point(int num)
{
    return num%13+1;
}

void show_hand_cards(int *buf,int length)
{
    for(int i=0;i<length;++i)
    {
        printf("%3d",get_card_point(buf[i]));
    }
    printf("\n");
}





