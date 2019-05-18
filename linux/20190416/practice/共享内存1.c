#include<sys/shm.h>
#include<stdio.h>
int main()
{
	int mmd=shmget(1001,sizeof(int),IPC_CREAT|IPC_EXCL);
	if(-1==mmd)
	{
		printf("创建失败\n");
		return -1;
	}
	else
	{
		int *a=(int *)shmat(mmd,NULL,SHM_RND);
		*a=190416;
		printf("a is %d\n",*a);
	}

	return 0;
}
