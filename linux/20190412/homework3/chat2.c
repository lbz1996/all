#include<stdio.h>
#include<sys/select.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main(int argc,char **argv)
{
	int fdw=open(argv[1],O_WRONLY);
	if(0>fdw)
	{
		printf("wrong in\n");
		return -1;
	}
	int fdr=open(argv[2],O_RDONLY);
	if(0>fdr)
	{
		printf("wrong in\n");
		return -1;
	}
	fd_set fd;
	int ret;
	char buf[128];
	printf("chat2 fdr=%d,fdw=%d\n",fdr,fdw);
	while(1)//双方都没断开就不退出
	{
		FD_ZERO(&fd);
		FD_SET(0,&fd);
		FD_SET(fdr,&fd);
		ret=select(fdr+1,&fd,NULL,NULL,0);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&fd))
			{
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
				if(ret==0)
				{
				printf("断开\n");
					break;
				}
				else
					printf("%s\n",buf);
			}
			if(FD_ISSET(0,&fd))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("断开\n");
					break;
				}
				write(fdw,buf,strlen(buf)-1);
			}
		}
	}
	close(fdw);
	close(fdr);
	return 0;
}

