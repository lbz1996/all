#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
int main()
{
	//守护进程的创建
	//1.创建子进程,父进程退出
	int pidr=fork();
	if(-1==pidr)
	{
		perror("fork1");
		return -1;
	}
	else if(0==pidr)
	{ 
	//2.在子进程中创建新会话
		pidr=setsid();
		if(-1==pidr)
		{
			perror("setsid");
			return -1;
		}
	//3.改变当前工作目录到根目录
		pidr=chdir("/");
		if(-1==pidr)
		{
			perror("pidr");
			return -1;
		}
	//4.重设文件权限掩码
		umask(0);
	//5.关闭所有不需要的文件描述符(最大为啥是64???)
		for(int i=0;i<64;++i)
			close(i);
		int fd=open("/tmp/log",O_WRONLY|O_CREAT|O_APPEND);//O_CREAT没有就创建,O_APPEND从文件结尾写
		if(-1==fd)   		 //好像只写就可以了?
		{
			perror("open2");
			return -1;
		}
		while(1)
		{
			sleep(5);
			if(-1==write(fd,"I have run 5s\n",sizeof("I have run 5s\n")))
			{
				perror("write3");
				return -1;
			}
		}
	}
	return 0;
}
