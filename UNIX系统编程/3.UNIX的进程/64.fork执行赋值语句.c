#include<stdio.h>
#include<unistd.h>
int main()
{
	int x=1;
	int ret;
	ret=fork();
	if(0==ret)
	{
		x+=1;
		printf("chilid x from %p\n",&x);
	}
	else
	{
		printf("chilid x from %p\n",&x);
	}
	return 0;
}
