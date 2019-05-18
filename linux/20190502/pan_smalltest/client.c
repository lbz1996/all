#include "head.h"
#include "sql_func.c"
#include "user_func.c"
#include "file_func.c"
int main(int argc,char **argv)
{
    int ret;
    char buf[128];
    bzero(buf,sizeof(buf));
    //链接服务端
    printf("Hello world\n");
    if(2!=argc)
    {
        printf("wrong input\n");
        return -1;
    }
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    FUNC_ERROR(socket_fd,-1,"socket"); 
    struct sockaddr_in sockaddr_in_0;
    bzero(&sockaddr_in_0,sizeof(struct sockaddr_in));
    sockaddr_in_0.sin_port=htons((short) 1234);
    sockaddr_in_0.sin_family=AF_INET;
    sockaddr_in_0.sin_addr.s_addr=inet_addr(argv[1]);
    ret=connect(socket_fd,(struct sockaddr*)&sockaddr_in_0,sizeof(sockaddr_in_0));
    FUNC_ERROR(ret,-1,"connect");
    //测试收发
    ret=recv(socket_fd,buf,5,0);
    printf("recv_ret is %d\n",ret);
    printf("%s\n",buf);
    printf("\n\n\n");
    char user_name[32]="lbz";
    //测试不断接收命令并发送
    char pwd[4096]="lbz";  
    int command_code=16;
    int command_result=0;

        bzero(buf,128);
        gets(buf);//scanf("%s",buf);
        //先识别命令,(不考虑参数合法才)发送命令码
        command_code=1;
        send(socket_fd,&command_code,sizeof(int),0);
        //获得参数
        //发送命令?还是就参数?
        send(socket_fd,buf,128,0);
        //对接执行命令
        if(16==command_code)//puts
        {
            client_upload_file(socket_fd,buf);
        }
        command_code=-1;
        //接收命令结果
        recv(socket_fd,&command_result,sizeof(int),0);
        printf("command_result is %d\n",command_result);
        if(1==command_result)
            printf("执行命令成功\n");
        else
        {
            printf("执行命令失败\n");
        }
    return 0;
}





