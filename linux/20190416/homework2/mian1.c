#include<sys/shm.h>
#include<string.h>
#include<stdio.h>
//sudo......
int main()
{
	int key=1234;
	int shmid=shmget(key,4096,IPC_CREAT);	
	if(-1==shmid)
	{
		perror("shmget");//perror好爽......
		printf("creat failure\n");
		return 0;
	}
	char *pshm;
	pshm=(char *)shmat(shmid,NULL,0);	
	if((char *) -1==pshm)
	{
		perror("shmat");
		printf("at failure\n");
		return -1;
	}
	strcpy(pshm,"How are you");
	shmdt(pshm);
	return 0;
}
