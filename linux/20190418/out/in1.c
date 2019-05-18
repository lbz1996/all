//in1
#include <signal.h>
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
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
typedef struct text
{
	int flag;
	char str[128];
}text,*ptext;
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
void routine(int p)
{
	int shmid1=shmget(1000,sizeof(text),IPC_CREAT);
	ptext ptext0=(ptext) shmat(shmid1,NULL,0);
	//写入到out1
	text a1;
	memset(&a1,0,sizeof(a1));
	a1.flag=4;
	strcpy(a1.str,"gg");
	memcpy(ptext0,&a1,sizeof(a1));
	exit(0);
}
int main(int argc,char **argv)
{
	int fdr=open(argv[1],0600|O_RDONLY);
	if(0>fdr)
	{
		printf("wrong in\n");
		return -1;
	}
	int fdw=open(argv[2],0600|O_WRONLY);
	if(0>fdw)
	{
		printf("wrong in\n");
		return -1;
	}
	printf("chat1 fdr=%d,fdw=%d\n",fdr,fdw);		
	fd_set fd;
	int ret;
	char buf[128];


	//建立共享内存
	int shmid1=shmget(1000,sizeof(text),IPC_CREAT);
	if(-1==shmid1)
	{
		perror("shmget");
	}
	ptext ptext0=(ptext) shmat(shmid1,NULL,0);
	//建立信号量(锁内存)
	int semid1=semget(1000,1,0600|IPC_CREAT);
	if(-1==semid1)
	{
		perror("semget");
	}
	union semun semun1;
	semun1.val=1;
	semctl(semid1,0,SETVAL,semun1);
	struct sembuf sembufP,sembufV;
	sembufP.sem_num=sembufV.sem_num=0;
	sembufP.sem_op=-1;sembufV.sem_op=1;
	sembufP.sem_flg=sembufV.sem_flg=SEM_UNDO;
	signal(SIGINT,routine); 
	while(1)
	{
		FD_ZERO(&fd);
		FD_SET(0,&fd);
		FD_SET(fdr,&fd);
		ret=select(fdw+1,&fd,NULL,NULL,0);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&fd))//fdr可读就开始读
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
					text a1;
					memset(&a1,0,sizeof(a1));
					a1.flag=1;
					strcpy(a1.str,buf);
					//printf("out1:%s\n",buf);
					semop(semid1,&sembufP,sizeof(sembufP));
					memcpy(ptext0,&a1,sizeof(a1));
					semop(semid1,&sembufV,sizeof(sembufV));
				}
			}
			if(FD_ISSET(0,&fd))//有标准输入
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("断开\n");
					routine(1);
					break;
				}
				//写入到out1
				text a1;
				memset(&a1,0,sizeof(a1));
				a1.flag=2;
				strcpy(a1.str,buf);
				//printf("out1:%s\n",buf);
				semop(semid1,&sembufP,sizeof(sembufP));
				memcpy(ptext0,&a1,sizeof(a1));
				semop(semid1,&sembufV,sizeof(sembufV));
				//写入到in2
				write(fdw,buf,strlen(buf)-1);			
			}
		}
	}
	close(fdr);
	close(fdw);
}

