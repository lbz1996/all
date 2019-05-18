#include<stdio.h>
#include<sys/select.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/msg.h>
typedef struct msgbuf
{
	long mtype; /* type of message */
	char mtext[128]; /* message text */
}msgbuf;
int main(int argc,char **argv)
{
	int msgid=msgget(1000,IPC_CREAT);
	if(0>msgid)
	{
		perror("msgget");
		return -1;
	}
	while(1)
	{
		msgbuf msgbuf0;
		msgrcv(msgid, &msgbuf0, sizeof(msgbuf0), 0, 0);
		if(4==msgbuf0.mtype)
		{
			break;
		}
		else if(3!=msgbuf0.mtype)
		{
			if(1==msgbuf0.mtype)//对面
			{ 
				printf("%s\n",msgbuf0.mtext);
			}
			if(2==msgbuf0.mtype)//自己
			{
				printf("      %s\n",msgbuf0.mtext);
			}
		}
	}
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}

