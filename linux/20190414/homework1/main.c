#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("pid is %d,ppid is %d\nuid is %d,gid is %d\neuid is %d,egid is %d\n",getpid(),getppid(),getuid(),getgid(),geteuid(),getegid());
	return 0;
}
