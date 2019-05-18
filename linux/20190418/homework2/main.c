#include<signal.h>
#include<stdio.h>
#include<strings.h>
#include<unistd.h>
void signcall1(int sign)
{
	printf("in 1\n");
	printf("out 1\n");
}

int main()
{
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_handler=signcall1;
	sigaction(SIGINT,&act,NULL);
	while(1)
	{
		sleep(3);
		printf("in main\n");
	}
	return 0;
}
