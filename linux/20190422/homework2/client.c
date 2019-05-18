#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include<unistd.h>
int main(int argc,char **argv)
{
	if(2!=argc)
	{
		printf("wrong in\n");
		return -1;
	}
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sock)
	{
		perror("sock");
		return -1;
	}

	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port=htons( (short) 1234);

	int ret;
	ret=connect(sock,(struct sockaddr*) &server,sizeof(server));
	if(-1==ret)
	{
		perror("connect");
	}
	else
		printf("connect success\n");
	char buf[128];
	fd_set fd;

	while(1)
	{
		FD_ZERO(&fd);
		FD_SET(0,&fd);
		FD_SET(sock,&fd);
		ret=select(sock+1,&fd,NULL,NULL,0);
		if(ret>0)
		{
			if(FD_ISSET(sock,&fd))
			{
				memset(buf,0,sizeof(buf));
				//ret=read(sock,buf,sizeof(buf));
				ret=recv(sock,buf,sizeof(buf),0);
				if(ret==0)
				{
				printf("断开\n");
					break;
				}
				else
					printf("%s",buf);
			}
			if(FD_ISSET(0,&fd))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("断开\n");
					break;
				}
				ret=send(sock,buf,sizeof(buf),0);
			}
		}
	}
	return 0;
}
