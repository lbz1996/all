#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char **argv)
{
	int pd=open(argv[1],O_RDONLY);
	printf("pd is %d\n",pd);
	return 0;
}
