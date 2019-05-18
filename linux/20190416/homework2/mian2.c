#include<sys/shm.h>
#include<string.h>
#include<stdio.h>
int main()
{
	int key=1234;
	int shmid=shmget(key,0,0);//取内存标识符只需00...	
	if(-1==shmid)
	{
		perror("shmget");
		printf("get failure\n");
		return 0;
	}
	printf("shmid is %d\n",shmid);
	void *pshm=shmat(shmid,NULL,SHM_RDONLY);//null直接让内存决定	
	if((void *) -1==pshm)
	{
		perror("shmat");
		printf("at failure\n");
		return -1;
	}
	printf("%s\n",(char *) pshm);
	shmdt(pshm);
	shmctl(shmid,IPC_RMID,0);//删除时无视buf,见man
	return 0;
}
