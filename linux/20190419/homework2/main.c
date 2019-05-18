#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
void cleanfunc(void *p)
{
	free(p);
}	
void *pthreadfunc1(void *p)
{
	int *a=(int *) malloc(sizeof(int));	
	pthread_cleanup_push(cleanfunc,(void*) a);
	read(STDIN_FILENO,a,sizeof(int));//???
	pthread_cleanup_pop(0);
	pthread_exit(NULL);
}

int main()
{
	pthread_t pthreadID;
	pthread_create(&pthreadID,NULL,pthreadfunc1,NULL);
	pthread_cancel(pthreadID);
	sleep(1);
	return 0;
}
