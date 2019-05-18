#include<stdio.h>
#include<unistd.h>
int main()
{
	int a=10;
	pid_t pidR=fork();
	if(0==pidR)
	{
		printf("children\n");
		printf("pid is %d,ppid is %d\n",getpid(),getppid());
		printf("a=%d\n",a);
		a+=5;
		while(1);
	}
	else
	{
		printf("father\n");
		printf("pid is %d,ppid is %d\n",getpid(),getppid());
		printf("a=%d\n",a);
		a+=3;
		sleep(1);
		while(1);	
	}
	return 0;
}
