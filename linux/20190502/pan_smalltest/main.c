#include "head.h"
#include "sql_func.c"
#include "user_func.c"
#include "file_func.c"
int main()
{
    //连接通信
    int ret;
    printf("Hello world\n");
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);       
    FUNC_ERROR(socket_fd,-1,"socket");
    struct sockaddr_in sockaddr_in_0;
    memset(&sockaddr_in_0,0,sizeof(struct sockaddr_in));
    sockaddr_in_0.sin_port=htons((short)1234);
    sockaddr_in_0.sin_family=AF_INET;
    sockaddr_in_0.sin_addr.s_addr=htonl(INADDR_ANY);
    socklen_t sockaddr_length=sizeof(struct sockaddr); 
    ret=bind(socket_fd,(struct sockaddr*) &sockaddr_in_0,sockaddr_length);
    FUNC_ERROR(ret,-1,"bind");
    ret=listen(socket_fd,10);
    FUNC_ERROR(ret,-1,"listen");
    int client_fd=accept(socket_fd,NULL,NULL);
    FUNC_ERROR(client_fd,-1,"accept");
    ret=send(client_fd,"hello",5,0);
    printf("send ret is %s\n","send");
    printf("\n\n\n");
    char buf[128];
    int command_code=16;
    int command_result=999;
        //接收命令码
        bzero(buf,128);
        recv(client_fd,&command_code,sizeof(int),0);
        //接收命令本身?(只有参数好像就可以)
        printf("command_code is %d\n",command_code);
        recv(client_fd,buf,128,0);
        //执行命令并获得结果
        if(16==command_result)
        {
            //server_recv_file (client_fd,buf,user_name);
        }
        command_code=-1;
        command_result=-1;
        //发送执行结果
        printf("command is %s\n",buf);
        send(client_fd,&command_result,sizeof(int),0);
    return 0;
}



















