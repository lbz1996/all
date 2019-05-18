#include "head.h"

int main(int argc,char **argv)
{
    int ret;
    printf("Hello world\n");
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    FUNC_ERROR(socket_fd,-1,"socket");
    struct sockaddr_in sockaddr_in_1;
    sockaddr_in_1.sin_family=AF_INET;
    sockaddr_in_1.sin_port=htons(1234);
    //sockaddr_in_1.sin_addr.s_addr=inet_addr(argv[1]);
    sockaddr_in_1.sin_addr.s_addr=inet_addr("172.19.210.35");
    int sockaddr_len=sizeof(struct sockaddr);
    ret=connect(socket_fd,(struct sockaddr *)&sockaddr_in_1,sockaddr_len);
    FUNC_ERROR(ret,-1,"connect");
    printf("socket_fd is %d\n",socket_fd);
    return 0;
}

