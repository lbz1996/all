#include<signal.h>
#include<stdio.h>
void signcall1(int sign)
{
	printf("in 1\n");
	while(1)
		printf("now 1\n");
	printf("out 1\n");
}
void signcall2(int sign)
{
	printf("in 2\n");
	while(1)
		printf("now 2\n");
	printf("out 2\n");
}


int main()
{
//	sighandler_t  ret=
	signal(SIGINT,signcall1);
//	if(SIG_ERR==ret)
//	{
//		perror("SIGINT");
//		return -1;
//	}
//	ret=
	signal(SIGQUIT,signcall2);
//	if(SIG_ERR==ret)
//	{
//		perror("SIGINT");
//		return -1;
//	}
	while(1)
		printf("in main\n");
	return 0;
}
