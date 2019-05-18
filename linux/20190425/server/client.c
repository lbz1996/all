#include "head.h"
int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("wrong in\n");
		return -1;
	}
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==socketFd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons((short)1234);
	ser.sin_addr.s_addr=inet_addr(argv[1]);//点分十进制转为32位的网络字节序
	int ret;
	ret=connect(socketFd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
    char buf[10];
    memset(buf,0,sizeof(char)*10);
    recv(socketFd,buf,5,0);
    printf("%s\n",buf);
	printf("connect success,");
    
    char buffer[1000];
    memset(buffer,0,sizeof(buffer));
    ret=recv(socketFd,buffer,sizeof(buffer),0);
    printf("ret is %d,sizeof(train) is %ld\n",ret,sizeof(train));
    printf("received file is %s",((train*)buffer)->buf);
    printf(" with %ld\n",((train*)buffer)->data_len);
    long file_len=((train*)buffer)->data_len;

}











