#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
int main(int argc,char **argv)
{
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	printf("a+b=%d\n",a+b);
	return 0;
}
