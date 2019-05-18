#include<stdio.h>
#include<unistd.h>
#include<errno.h>
int readline(int fd,char *buf,int nbytes)
{
	int numread=0;
	int returnval;
	while(numread<nbytes-1)
	{
		returnval=read(fd,buf+numread,1);
		if( (-1==returnval) && (errno==EINTR))
			continue;
		if( (0==returnval) && (0==numread) )
			return 0;
		if(0==returnval)
			break;
		if(0==returnval)
			return -1;
		++numread;
		if(buf[numread-1]=='\n')
		{
			buf[numread]='\0';
			return numread;
		}
	}
	errno=EINVAL;
	return -1;
}
int main()
{
	char in[100];
	while(1)
	{
		readline(STDIN_FILENO,in,100);
		printf("%s",in);
	}
}
