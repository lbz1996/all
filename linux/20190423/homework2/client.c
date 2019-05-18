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
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(-1==sock)
	{
		perror("sock");
		return -1;
	}

	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_addr.s_addr = inet_addr(argv[1]);
	client.sin_port=htons( (short) 1234);

	char buf[128];
	int ret;
	ret=sendto(sock,"g",1,0,(struct sockaddr*) &client,sizeof(client));
	if(-1==ret)
	{
		perror("sendto");
		return -1;
	}
	else
	{
		printf("connect success\n");
	}

	fd_set fd;
	while(1)
	{
		FD_ZERO(&fd);
		FD_SET(0,&fd);
		FD_SET(sock,&fd);
		ret=select(sock+1,&fd,NULL,NULL,0);
		if(FD_ISSET(sock,&fd))
		{
			memset(buf,0,sizeof(buf));
			ret=recvfrom(sock,buf,sizeof(buf),0,NULL,NULL);
			if(ret==0)
			{
				printf("断开\n");
				break;
			}
			printf("%s\n",buf);
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
			ret=sendto(sock,buf,sizeof(buf)-1,0,(struct sockaddr*) &client,sizeof(client));
			if(-1==ret)
			{
				printf("sendto");
				return -1;
			}
		}
	}
	return 0;
}
