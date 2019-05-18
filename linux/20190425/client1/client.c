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

    train train0;
    memset(&train0,0,sizeof(train));
    ret=recv(socketFd,&train0,sizeof(train),0);
    printf("ret=%d,sizeof(train) is %ld\n",ret,sizeof(train));
    printf("received is %s with %ld\n",train0.buf,train0.data_len);

    long file_len=train0.data_len;
    int new_file_fd=open("new_file",O_CREAT|O_APPEND|O_RDWR,0777);
    long recved=0;
    while(recved<=file_len)
    {
        memset(&train0,0,sizeof(train));
        ret=recv(socketFd,&train0,sizeof(train),0);
        printf("ret is %d\n",ret);
        if(-1==ret)
        {
            perror("recv");
            return -1;
        }
        if(0==ret||-1==train0.data_len)
        {
            printf("over\n");
            break;
        }
        write(new_file_fd,train0.buf,train0.data_len);
        recved+=train0.data_len;
    }
    return 0;
}











