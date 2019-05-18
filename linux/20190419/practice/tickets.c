#include<stdio.h>
#include<pthread.h>
typedef struct 
{
	int flag;
	pthread_mutex_t mutex;
}data;
void *pthreadfunc1(void *p)
{
	data data0;
	data0=*((data*) p);
	int count=0;
	while(1)
	{
		pthread_mutex_lock(&data0.mutex)
		if
		count++;
		printf("I am func1:sell %d\n",count);
	}
	return NULL;
}
void *pthreadfunc2(void *p)
{
	int count=0;
	while(1)
	{
		count++;
		printf("I am func2:sell %d\n",count);
	}
	return NULL;
}
int main()
{
	pthread_mutex_t mutex;	
	pthread_mutex_init(&mutex,NULL);
	data data0;
	data0.flag=2000000;
	data0.mutex=mutex;
	pthread_t threadid1,threadid2;
	pthread_create(&threadid1,NULL,pthreadfunc1,&data0);		
	pthread_create(&threadid2,NULL,pthreadfunc2,&data0);
	while(1);
	return 0;
}
