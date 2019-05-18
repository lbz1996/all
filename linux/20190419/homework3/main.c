#include<stdio.h>
#include<pthread.h>
int a;
void* pthreadfunc1(void *p)
{
	pthread_mutex_t mutexID=*((pthread_mutex_t *)p);
	for(int i=1;i<=10000000;++i)
	{
		pthread_mutex_lock(&mutexID);
		++a;
		pthread_mutex_unlock(&mutexID);
	}
	pthread_exit(NULL);	
}

int main()
{
	pthread_mutex_t mutexID;
	pthread_mutex_init(&mutexID,NULL);
	a=0;
	pthread_t pthreadID;
	pthread_create(&pthreadID,NULL,pthreadfunc1,&mutexID);
	for(int i=1;i<=10000000;++i)
	{
		pthread_mutex_lock(&mutexID);
		++a;
		pthread_mutex_unlock(&mutexID);
	}
	pthread_join(pthreadID,NULL);
	printf("a is %d\n",a);
	return 0;	
}
