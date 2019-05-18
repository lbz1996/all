#include<stdio.h>
#include<stdlib.h>
int add(int a,int b);
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("wrong input\n");
		return -1;
	}
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	printf("伪目标通过$()调用替换,.PHONY声明,啥个顺序?\n");
	printf("自动变量用$开头,@是目标,^是所有依赖文件,<是第一个依赖,?是更新的所有相关文件\n"); 		
	printf("隐含规则:o自动依赖.c/.cpp(同名)\n同理:可执行依赖c\n但是好像目标文件的依赖要写出来(依赖都不用写...)\n");
	printf("要用的.c在其他目录怎么搞?\n");
	printf("a+b=%d\n",add(a,b));
	return 0;
}
