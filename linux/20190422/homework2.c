#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
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
	ret=send(sock,"hello",5,0);
	if(-1==ret)
	{
		perror("send");
		return -1;
	}
	char buf[128];
	ret=recv(sock,buf,sizeof(buf),0);
	if(-1==ret)
	{
		perror("recv");
		return -1;
	}
	printf("server gets %s",buf);
	return 0;
}
