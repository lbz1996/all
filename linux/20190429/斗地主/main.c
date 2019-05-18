#include "head.h"
int main()
{
    int ret;
    phall phall0= (phall) calloc(1,sizeof(hall));


    int socket_fd;
    socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socket_fd)
    {
        printf("testline %d:",__LINE__);
        perror("socket");
    }
    else
        printf("socket_fd is %d\n",socket_fd);
    struct sockaddr_in sockaddr_in0;









    return 0;
}

