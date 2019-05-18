#include<stdio.h>
#include<unistd.h>
int main()
{
	int a=10;
	pid_t pid=fork();
	if(0==pid)
	{
		printf("now is kid= %d,a is %d\n",getpid(),a);
		return 0;
	}
	else
	{
		printf("now is parent= %d,a is %d\n",getpid(),a);
		a+=5;
		printf("a is %d\n",a);
		sleep(1);
	}
	return 0;
}
