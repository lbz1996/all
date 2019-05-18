#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/wait.h>
int main()
{
	int key=1234;
	int shmid=shmget(key,sizeof(int),IPC_CREAT);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	int *pshm=(int *)shmat(shmid,NULL,SHM_RND);
	if((int *) -1 ==pshm)
	{
		perror("shmat");
		return -1;
	}
	*pshm=0;
	int ret=fork();
	if(0==ret)
	{
		for(int i=1;i<=100000000;++i)
			*pshm+=1;
		printf("%d\n",*pshm);
	}
	else
	{
		wait(NULL);
		for(int i=1;i<=100000000;++i)
			*pshm+=1;
		printf("%d\n",*pshm);
	}
	return 0;
}
