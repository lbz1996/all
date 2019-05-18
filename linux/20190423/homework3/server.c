#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include<string.h>
#include<sys/epoll.h>
int main()
{
	int ret;
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sock)
	{
		perror("sock");
		return -1;
	}
	int reuse=1;
	ret=setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));	
	if(-1==ret)
	{
		perror("setsockopt");
		return -1;
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port=htons( (short) 1234);

	ret=bind(sock,(struct sockaddr *)&server,sizeof(server));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}

	ret=listen(sock,10);
	if(-1==ret)
	{
		perror("listen");
		return -1;
	}

	int new_fd;
	struct sockaddr_in client;
	unsigned int addrlen=sizeof(client);
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

	while(1)
	{
		memset(eventarg,0,sizeof(eventarg));
		readynum=epoll_wait(epollid,eventarg,3,-1);
		//printf("%d\n",readynum);
		//sleep(1);
		for(i=0;i<readynum;++i)
		{

			if(sock==eventarg[i].data.fd)
			{
				new_fd=accept(sock,(struct sockaddr*) &client,&addrlen);
				printf("client is %s,pot is %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));	
				event.data.fd=new_fd;
				epoll_ctl(epollid,EPOLL_CTL_ADD,new_fd,&event);
			}

			if(new_fd==eventarg[i].data.fd)
			{
				memset(buf,0,sizeof(buf));
				ret=recv(new_fd,buf,sizeof(buf),0);
				if(ret==0)
				{
					printf("断开,等待重连\n");
					event.events=EPOLLIN;
					event.data.fd=new_fd;
					epoll_ctl(epollid,EPOLL_CTL_DEL,new_fd,&event);
					close(new_fd);
					continue;
				}
				printf("%s",buf);
			}

			if(0==eventarg[i].data.fd)
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("断开");
					goto over;
				}
				ret=send(new_fd,buf,strlen(buf)-1,0);
			}

		}
	}

over:
	close(new_fd);
	close(sock);
	return 0;
}
