#include<signal.h>
#include<stdio.h>
#include<strings.h>
#include<unistd.h>
//一号信号屏蔽二号信号
void signcall1(int sign)
{
	printf("in 1\n");
	sleep(1);
	struct sigaction actout;
	bzero(&actout,sizeof(actout));
	sigpending(&actout.sa_mask);
	if(sigismember(&actout.sa_mask,SIGQUIT))
		printf("SIGQUIT is pending\n");
	else
		printf("SIGQUIT is not pending\n");
	printf("out 1\n");
}
void signcall2(int sign)
{
	printf("in 2\n");
	printf("out 2\n");
}

int main()
{
	struct sigaction act2;
	bzero(&act2,sizeof(act2));
	act2.sa_handler=signcall2;
	sigaction(SIGINT,&act2,NULL);

	struct sigaction act1;
	bzero(&act1,sizeof(act1));
	act1.sa_handler=signcall1;
	sigemptyset(&act1.sa_mask);
	sigaddset(&act1.sa_mask,SIGINT);
	sigaction(SIGQUIT,&act1,NULL);

	while(1)
	{
		sleep(3);
		printf("in main\n");
	}
	return 0;
}
