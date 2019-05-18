#include <sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int pd=open(argv[1],O_RDWR);
	if(0>pd)
	{
		printf("wrong input\n");
		return -1;
	}
	void *ppp=mmap(0,3,PROT_WRITE,MAP_SHARED,pd,0);	
	strcpy((char *) ppp,"WORLD");//不强转它就会标红......
	munmap(ppp,5);
	return 0;
}

