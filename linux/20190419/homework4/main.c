#include<stdio.h>
#include<pthread.h>
int count1,count2;
typedef struct 
{
	int tickets;
	pthread_mutex_t mutexID;
	pthread_mutex_t mutexID3;
	pthread_cond_t cond3;
}data;

void *pthreadfunc1(void*p)
{
	data* data0=(data*)p;
	while(1)
	{
		pthread_mutex_lock(&data0->mutexID);
		if(data0->tickets>0)
		{
			//printf("func1 sell %d\n",data0->tickets);
			data0->tickets--;
			++count1;
			if(0==data0->tickets)
				pthread_cond_signal(&data0->cond3);
			pthread_mutex_unlock(&data0->mutexID);
		}
		else
		{
			pthread_mutex_unlock(&data0->mutexID);
			pthread_exit(NULL);
		}
	}
}
void *pthreadfunc2(void*p)
{
	data* data0=(data*)p;
	while(1)
	{
		pthread_mutex_lock(&data0->mutexID);
		if(data0->tickets>0)
		{
			//printf("func2 sell %d\n",data0->tickets);
			data0->tickets--;
			++count2;
			if(data0->tickets==0)
				pthread_cond_signal(&data0->cond3);
			pthread_mutex_unlock(&data0->mutexID);
		}
		else
		{
			pthread_mutex_unlock(&data0->mutexID);
			pthread_exit(NULL);
		}
	}
}

void *pthreadfunc3(void*p)
{
	data* data0=(data*)p;
	pthread_mutex_lock(&data0->mutexID3);
	pthread_cond_wait(&data0->cond3,&data0->mutexID3);
	((data*)p)->tickets=200000;
	pthread_mutex_unlock(&data0->mutexID3);
	pthread_cond_destroy(&data0->cond3);
	pthread_exit(NULL);
}

int main()
{
	count1=count2=0;

	pthread_mutex_t mutexID;
	pthread_mutex_init(&mutexID,NULL);

	int tickets=200000;
	data data0;
	pthread_mutex_t mutexID3;
	pthread_mutex_init(&mutexID3,NULL);
	pthread_cond_t cond3;
	pthread_cond_init(&cond3,NULL);
	data0.mutexID=mutexID;
	data0.tickets=tickets;
	data0.mutexID3=mutexID3;
	data0.cond3=cond3;

	pthread_t pthreadID1;
	pthread_create(&pthreadID1,NULL,pthreadfunc1,&data0);
	pthread_t pthreadID2;
	pthread_create(&pthreadID2,NULL,pthreadfunc2,&data0);
	pthread_t pthreadID3;
	pthread_create(&pthreadID3,NULL,pthreadfunc3,&data0);

	pthread_join(pthreadID1,NULL);
	pthread_join(pthreadID2,NULL);
	printf("1 sell %d,2 sell %d\n",count1,count2);
	return 0;
}
