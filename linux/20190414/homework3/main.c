#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	int a=0;//声明一个变量
	char b[15]="string";//声明一个字符串
	pid_t pidR=fork();
	if(0==pidR)
	{
		printf("child\n");
		printf("return ed pidR is %d\n",pidR);	
		printf("pid is %d,ppid is %d\n",getpid(),getppid());
		printf("a is %d,b is %s\n",a,b);
		printf("a from %x,b from %x\n",&a,b);	
		a+=2;
		printf("a is %d,b is %s\n",a,b);
		printf("a from %x,b from %x\n",&a,b);	
		strcpy(b,"changed again");
		printf("child over\n");
	}
	else
	{
		printf("parent\n");
		printf("return ed pidR is %d\n",pidR);	
		printf("pid is %d,ppid is %d\n",getpid(),getppid());
		printf("a is %d,b is %s\n",a,b);
		printf("a from %x,b from %x\n",&a,b);	
		a+=1;
		strcpy(b,"changed");
		printf("a is %d,b is %s\n",a,b);
		printf("a from %x,b from %x\n",&a,b);
		printf("parent over\n");
		sleep(1);	
	}
	printf("a is %d,b is %s\n",a,b);
	printf("a from %x,b from %x\n",&a,b);
	printf("gg\n");	
	return 0;
}
