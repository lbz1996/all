#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<sys/types.h>
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int main()
{
	//创建一个信号量
	int semid=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
	if(-1==semid)
	{
		perror("semid");
		return -1;
	}	
	//初始化
	union semun semun1;
	semun1.val=0;
	semctl(semid,0,SETVAL,semun1);
	//printf("now semval is %d\n",semctl(semid,0,GETVAL));
	//设置arg参数
	struct sembuf s1,s2;
	s1.sem_num=s2.sem_num=0;//
	s1.sem_op=1;
	s2.sem_op=-1;
	s1.sem_flg=s2.sem_flg=0;
	int ret=fork();
	if(0==ret)
	{
		while(1)
		{
			if(20>=semctl(semid,0,GETVAL))
			{
				//semop(semid,&s2,1);
				//printf("child is %d\n",semctl(semid,0,GETVAL));
				semop(semid,&s1,1);
				printf("make %d\n",semctl(semid,0,GETVAL));
				sleep(1);
			}
			else
				break;
		}
	}
	else
	{
		int a=0;
		while(1)
		{
			sleep(2);
			if(0<=semctl(semid,0,GETVAL))
			{
				semop(semid,&s2,1);
				printf("bought is %d\n",++a);
			}
			else
				break;
		}
	}
	semctl(semid,0,IPC_RMID);
	return 0;
}
