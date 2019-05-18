#include<signal.h>
#include<stdio.h>
void signcall(int signnum)
{
	printf("sign shows\n");
}
int main()
{
	//signal(SIGINT,signcall);//注册信号处理函数
	//signal(SIGINT,SIG_IGN);//忽略信号
	signal(SIGINT,SIG_DFL);//按照默认进行处理
	//hrtime是啥意思????
	while(1);
	return 0;
}
