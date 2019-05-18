//in2
#include<signal.h>
#include<stdio.h>
#include<sys/select.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/msg.h>
#include<stdlib.h>
typedef struct msgbuf 
{
	long mtype; /* type of message */
	char mtext[128]; /* message text */
}msgbuf;
void routine(int p)
{
	//创建一个消息队列
	int msgid=msgget(1000,IPC_CREAT);
	if(0>msgid)
		perror("msgget");
	msgbuf msgbuf0;
	msgbuf0.mtype=4;
	strcpy(msgbuf0.mtext,"gg");
	msgsnd(msgid,&msgbuf0,sizeof(msgbuf0),0);
	exit(0);
}

int main(int argc,char **argv)
{
	int fdw=open(argv[1],O_WRONLY);
	if(0>fdw)
	{
		printf("wrong in\n");
		return -1;
	}
	int fdr=open(argv[2],O_RDONLY);
	if(0>fdr)
	{
		printf("wrong in\n");
		return -1;
	}
	fd_set fd;
	int ret;
	char buf[128];
	printf("chat2 fdr=%d,fdw=%d\n",fdr,fdw);
	//创建一个消息队列
	int msgid=msgget(1000,IPC_CREAT);
	if(0>msgid)
	{
		perror("msgget");
		return -1;
	}
	signal(SIGINT,routine);
	while(1)//双方都没断开就不退出
	{
		FD_ZERO(&fd);
		FD_SET(0,&fd);
		FD_SET(fdr,&fd);
		ret=select(fdr+1,&fd,NULL,NULL,0);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&fd))//对面有消息
			{
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
				if(ret==0)
				{
					printf("断开\n");
					routine(1);
					break;
				}
				else
				{
					printf("%s\n",buf);
					msgbuf msgbuf0;
					msgbuf0.mtype=1;
					strcpy(msgbuf0.mtext,buf);
					msgsnd(msgid,&msgbuf0,sizeof(msgbuf0),0);
				}
			}
			if(FD_ISSET(0,&fd))//标准输入有消息
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("断开\n");
					routine(1);
					break;
				}
				msgbuf msgbuf0;
				msgbuf0.mtype=2;
				strcpy(msgbuf0.mtext,buf);
				msgsnd(msgid,&msgbuf0,sizeof(msgbuf0),0);
				write(fdw,buf,strlen(buf)-1);
			}
		}
	}
	close(fdw);
	close(fdr);
	return 0;
}

