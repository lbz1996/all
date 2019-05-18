#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include<string.h>
int main()
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sock)
	{
		perror("sock");
		return -1;
	}

	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port=htons( (short) 1234);

	int ret=bind(sock,(struct sockaddr *)&server,sizeof(server));
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
	new_fd=accept(sock,(struct sockaddr*) &client,&addrlen);
	printf("client is %s,pot is %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

	int fdmax=new_fd>sock?new_fd:sock;
	char buf[128];
	while(1)
	{
		fd_set fd;
		FD_ZERO(&fd);
		FD_SET(0,&fd);
		FD_SET(new_fd,&fd);

		if(0<select(fdmax+1,&fd,NULL,NULL,NULL))
		{
			if(FD_ISSET(0,&fd))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("断开");
					break;
				}
				//write(new_fd,buf,strlen(buf)-1);
				ret=send(new_fd,buf,strlen(buf)-1,0);
			}
			if(FD_ISSET(new_fd,&fd))
			{
				memset(buf,0,sizeof(buf));
				//ret=read(sock,buf,sizeof(buf));
				ret=recv(new_fd,buf,sizeof(buf),0);
				if(ret==0)
				{
					printf("断开\n");
					break;
				}
				else
					printf("%s",buf);
			}
		}
	}
	close(new_fd);
	close(sock);
	return 0;
}
