#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
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
	char buf[128]={0};
	ret=recv(new_fd,buf,sizeof(buf),0);
	if(-1==ret)
	{
		perror("recv");
		return -1;
	}
	printf("server gets %s",buf);
	ret=send(new_fd,"world\n",6,0);
	if(-1==ret)
	{
		perror("send");
		return -1;
	}
	close(new_fd);
	close(sock);
	return 0;
}
