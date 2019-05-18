#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
typedef struct student
{
	int number;
	char name[25];
	float score;
}stu,*pstu;

int main(int argc,char **argv)
{
	stu stuarr[3];
	float score=58;
	for(int i=0,j=1000;i<3;++i)
	{
		stuarr[i].number=j++;
		stuarr[i].score=score++;
	}
	strcpy(stuarr[0].name,"stu1\0");
	strcpy(stuarr[1].name,"stu2\0");
	strcpy(stuarr[2].name,"stu3\0");

	int pd=open(argv[1],O_RDWR);
	printf("pd is %d\n",pd);
	if(pd<0)
	{
		printf("wrong file\n");
		return -1;
	}
	for(int i=0;i<3;++i)
	{
		char strin[100];
		memset(strin,0,sizeof(strin));
		sprintf(strin,"%d %s %lf\n",stuarr[i].number,stuarr[i].name,stuarr[i].score);
		write(pd,strin,sizeof(int)+sizeof(' ')*2+sizeof(float)+sizeof(char)*20+sizeof('\n'));
	}
	lseek(pd,0,SEEK_SET);
	char save[100];
	memset(save,0,sizeof(save));
	for(int i=0;i<3;++i)
	{	
		read(pd,save,sizeof(int)+sizeof(' ')*2+sizeof(float)+sizeof(char)*20+sizeof('\n'));//传多少要收多少.
		printf("%s",save);
	}
	close(pd);//不关再运行pd就会出错......
	return 0;
}

