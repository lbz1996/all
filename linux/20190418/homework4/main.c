#include<signal.h>
#include<stdio.h>
#include<strings.h>
#include<unistd.h>
int main()
{
	//全程阻塞
	struct sigaction act;
	bzero(&act,sizeof(act));
	sigaddset(&act.sa_mask,SIGINT);
	sigprocmask(SIG_BLOCK,&act.sa_mask,NULL);
	//睡
	sleep(5);
	//判断是否挂起
	struct sigaction actout;
	bzero(&actout,sizeof(actout));
	sigpending(&actout.sa_mask);
	if(sigismember(&actout.sa_mask,SIGINT))
		printf("SIGINT is pending\n");
	else
		printf("SIGINT is not pending\n");
	//解除全程阻塞
	sigprocmask(SIG_UNBLOCK,&act.sa_mask,NULL);
	return 0;
}
