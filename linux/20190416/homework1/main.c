#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main()
{
	int fildes[2];
	int ret=pipe(fildes);//管道打开的也是文件描述符
	if(-1==ret)
	{
		printf("pipe failure\n");	
		return -1;
	}
	//他俩的运行顺序是完全随机的
	//取决于系统调度???
	if(0==fork())
	{
		sleep(10);
		char in[]="Hello";
		write(fildes[1],in,strlen(in));
		close(fildes[1]);
	}
	else
	{
		char out[10];
		memset(out,0,sizeof(out));
		read(fildes[0],out,10);
		//p92
		//read读取字节数跟文件内容有关
		//返回值还与文件类型有关
		//p181
		//在管道上调用read时,管道非空,read就会立刻返回;
		//管道为空,只要有进程为写操作打开管道,read就会一直阻塞到某些内容写入管道为止(???会等他写完嘛?)
		//p182是啥意思?
		printf("out is %s",out);
	}
	return 0;
}
