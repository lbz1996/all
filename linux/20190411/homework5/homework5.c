#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<string.h>
int Like_ls_l(char *dir)
{
	//total 4
	//-rw-rw-r-- 1 lbz lbz 767 Apr 11 23:59 homework5.c
	DIR *it;
   	if(!(it=opendir(dir)))
	{
		printf("wrong input path\n");
		return -1;
	}
	struct dirent *itdir;
	while(NULL!=(itdir=readdir(it)))
   	{
		struct stat buf;
		char newpath[560];
		memset(newpath,0,sizeof(newpath));
	if(0<sprintf(newpath,"%s/%s",dir,itdir->d_name))
		if(strcmp(itdir->d_name,".")!=0)
			if(strcmp(itdir->d_name,"..")!=0)
			{
				stat(newpath,&buf);
				char time[40];
				memset(time,0,sizeof(time));
				strcpy(time,ctime(&buf.st_mtime)+4);
				//memset(time+12,0,sizeof(time)-12*sizeof(char));
				time[12]=0;
				char rwx[11];
				memset(rwx,0,sizeof(rwx));
				rwx[0]='g';//文件类型是啥字母啊???拿啥弄啊?
				int rwxn=buf.st_mode;
				//while(rwxn>0)
				//{
				//	printf("%d ",rwxn&1);
				//	rwxn=rwxn>>1;
				//}
				for(int i=9;i>0;--i)
				{
					if(i%3==0)
						rwx[i]=rwxn&1?'x':'-';
					else if(i%3==1)
						rwx[i]=rwxn&1?'r':'-';
					else if(i%3==2)	
						rwx[i]=rwxn&1?'w':'-';
					rwxn=rwxn>>1;
				}
				//printf("%d\n",rwxn);
				//printf("%s\ngg:",rwx);
				printf("%s gg  %ld %s %s %10ld %s %s\n", rwx, buf.st_nlink,
					getpwuid(buf.st_uid)->pw_name, getgrgid(buf.st_gid)->gr_name,
					buf.st_size  ,  time  ,  itdir->d_name);				
			}
	}
	return 0;
}

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("wrong input\n");
		return -1;
	}
	char path[1000];
	memset(path,0,sizeof(path));
	Like_ls_l(argv[1]);	
	return 0;
}
