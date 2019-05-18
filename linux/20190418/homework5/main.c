#include<sys/time.h>
#include<stdio.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>
time_t init1;
time_t init2;
time_t init3;
void signcall1(int sign)
{
	printf("真实:%ld秒\n",++init1);
}
void signcall2(int sign)
{
	printf("虚拟:%ld秒\n",++init2);
}
void signcall3(int sign)
{
	printf("实用:%ld秒\n",++init3);
}


int main()
{
	init1=init2=init3=0;
	struct itimerval val;
	val.it_value.tv_sec=1;//初始值不能为0
	val.it_value.tv_usec=0;
	val.it_interval.tv_sec=1;
	val.it_interval.tv_usec=0;
	setitimer(ITIMER_REAL,&val,NULL);
	setitimer(ITIMER_VIRTUAL,&val,NULL);
	setitimer(ITIMER_PROF,&val,NULL);
	signal(SIGALRM,signcall1);
	signal(SIGVTALRM,signcall2);
	signal(SIGPROF,signcall3);	
	sleep(5);
	while(1);
}
