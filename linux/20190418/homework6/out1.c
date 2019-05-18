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
int main(int argc,char **argv)
{
	//获得共享内存
	int shmid1=shmget(1000,sizeof(text),IPC_CREAT);
	if(-1==shmid1)
	{
		perror("shmget");
	}
	printf("shmid1 is %d\n",shmid1);
	ptext ptext0=(ptext) shmat(shmid1,NULL,0);
	if((void*)-1==ptext0)
	{
		perror("shmat");
	}
	//获得信号量(锁内存)
	int semid1=semget(1000,0,IPC_CREAT);
	printf("senid is %d\n",semid1);
	if(-1==semid1)
	{
		perror("semget");
	}
	struct sembuf sembufP,sembufV;
	sembufP.sem_num=sembufV.sem_num=0;
	sembufP.sem_op=-1;sembufV.sem_op=1;
	sembufP.sem_flg=sembufV.sem_flg=SEM_UNDO;
	while(1)
	{
		semop(semid1,&sembufP,sizeof(sembufP));
		if(4==ptext0->flag)
		{
			break;
		}
		else if(3!=ptext0->flag)
		{
			if(1==ptext0->flag)
				printf("%d:%s\n",ptext0->flag,ptext0->str);
			if(2==ptext0->flag)
				printf("                             %d:%s\n",ptext0->flag,ptext0->str);
			ptext0->flag=3;
		}
		semop(semid1,&sembufV,sizeof(sembufV));
	}
		semop(semid1,&sembufV,sizeof(sembufV));
	shmctl(shmid1, IPC_RMID,NULL);
	semctl(semid1,0,IPC_RMID);
	return 0;
}

