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
	int ret;
	int sock=socket(AF_INET,SOCK_DGRAM,0);
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


	char buf[128];
	
	struct sockaddr_in client;
	unsigned int addrlen=sizeof(client);
	ret=recvfrom(sock,buf,1,0,(struct sockaddr*) &client,&addrlen);
	if(-1==ret)
	{
		perror("recvfrom");
		return -1;
	}
	printf("client is %s ,port is %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));	

	fd_set fd,fd_saved;
	FD_ZERO(&fd_saved);
	FD_SET(0,&fd_saved);
	FD_SET(sock,&fd_saved);

	while(1)
	{
		memcpy(&fd,&fd_saved,sizeof(fd_set));	
		ret=select(10+1,&fd,NULL,NULL,NULL);
		if(FD_ISSET(sock,&fd))
		{
			memset(buf,0,sizeof(buf));
			ret=recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*) &client,&addrlen);
			if(ret==0)
			{
				printf("断开\n");
				break;
			}
			printf("%s",buf);
		}
		if(FD_ISSET(0,&fd))
		{
			memset(buf,0,sizeof(buf));
			ret=read(0,buf,sizeof(buf));
			if(0==ret)
			{
				printf("断开");
				break;
			}
			ret=sendto(sock,buf,strlen(buf)-1,0,(struct sockaddr*) &client,addrlen);
			if(ret==0)
			{
				perror("sendto");
				break;
			}
		}

	}
	close(sock);
	return 0;
}
