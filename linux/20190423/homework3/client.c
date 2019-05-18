#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/epoll.h>
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
	unsigned int serverlong=sizeof(server);
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


	int epollid=epoll_create(1);
	if(-1==epollid)
	{
		perror("epoll");
		return -1;
	}


	struct epoll_event event,eventarg[3];
	event.events=EPOLLIN;
	event.data.fd=STDIN_FILENO;
	ret=epoll_ctl(epollid,EPOLL_CTL_ADD,0,&event);

	event.data.fd=sock;
	epoll_ctl(epollid,EPOLL_CTL_ADD,sock,&event);
	int i,readynum;
	int new_fd;
	new_fd=accept(sock,(struct sockaddr*) &server,&serverlong);
	printf("client is %s,pot is %d\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));
//	sleep(5);
	event.data.fd=new_fd;
	epoll_ctl(epollid,EPOLL_CTL_ADD,new_fd,&event);
	while(1)
	{
		memset(eventarg,0,sizeof(eventarg));
		readynum=epoll_wait(epollid,eventarg,3,-1);
		for(i=0;i<readynum;++i)
		{

			if(sock==eventarg[i].data.fd)
			{
				memset(buf,0,sizeof(buf));
				ret=recv(sock,buf,sizeof(buf),0);
				if(ret==0)
				{
					printf("断开\n");
					goto over;
				}
				else
					printf("%s\n",buf);
			}
			if(0==eventarg[i].data.fd)
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("断开\n");
					goto over;
				}
				ret=send(sock,buf,sizeof(buf),0);
			}
		}
	}
over:
	close(sock);
	close(new_fd);
	return 0;
}
