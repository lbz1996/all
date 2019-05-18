#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>
int FindFileInDir(char *dir,char *file)
{
	int flag=-1;
	//printf("current dir is %s\n",getcwd(dir,strlen(dir)));
	DIR *it;
   	if(!(it=opendir(dir)))
	{
		//printf("wrong input path\n");
		return flag;
	}
	struct dirent *itdir;
	while(NULL!=(itdir=readdir(it)))
   	{
		if(strcmp(itdir->d_name,file)==0)
		{
			printf("Finded.\n%s\n",dir);
			flag=0;
			break;
		}
		else if(itdir->d_type==4)
		{
			//printf("the new dir is %s\n",itdir->d_name);
			char newpath[256];
			memset(newpath,0,sizeof(newpath));
			if(strcmp(itdir->d_name,".")!=0)
				if(strcmp(itdir->d_name,"..")!=0)
					if(0<sprintf(newpath,"%s/%s",dir,itdir->d_name))
						if( FindFileInDir(newpath,file) == 0 )
							return 0;
		}
	}
	//printf("don't exits\n");
	return flag;
}

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("wrong input\n");
		return -1;
	}
	char path[1000];
	memset(path,0,sizeof(path));
	getcwd(path,sizeof(path));
	//printf("%s\n",path);//
	//printf("%s\n",getcwd(NULL,0));//单纯调用的时候这样更爽...
	if(0!=FindFileInDir(argv[1],argv[2]))
		printf("doesn't exist\n");
	return 0;
}
