#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid)
	{
		printf("child\n");
		printf("pid is %d,ppid is %d\n",getpid(),getppid());
		while(1);
	}
	else
	{
		printf("parent\n");
		printf("pid is %d,ppid is %d\n",getpid(),getppid());
		while(1);	
	}
	return 0;
}
