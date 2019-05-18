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
	int key=1234;
	int shmid=shmget(key,sizeof(int),IPC_CREAT);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}

	int *pshm=(int *)shmat(shmid,NULL,0777|SHM_RND);
	if((int *) -1 ==pshm)
	{
		perror("shmat");
		return -1;
	}
	*pshm=20;
	//创建一个信号量
	int semid=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
	if(-1==semid)
	{
		perror("semid");
		return -1;
	}
	
	//初始化
	union semun semun1;
	semun1.val=20;
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
		int a=0;
		while(1)
		{	
			if(0>=semctl(semid,0,GETVAL))
				break;
			semop(semid,&s2,1);
			printf("a sell %d\n",++a);
		}
		printf("out\n");
	}
	else
	{
		int b=0;
		while(1)
		{
			if(0>=semctl(semid,0,GETVAL))
				break;
			semop(semid,&s2,1);
			printf("b sell %d\n",++b);
		}
		printf("out\n");
	}
	shmctl(shmid,0,IPC_RMID);
	semctl(semid,0,IPC_RMID);
	return 0;
}
