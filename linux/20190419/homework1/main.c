#include<stdio.h>
#include<pthread.h>
typedef struct
{
	int num;
}data;
void *pthreadfunc1(void *p)
{
	data *pdata1=(data*) p;
	printf("num is %d in pthreadfunc1\n",pdata1->num);
	pdata1->num=1;
	pthread_exit((void*) pdata1);
}
int main()
{
	data data0;
	data0.num=99;
	pthread_t pthreadid0;
	pthread_create(&pthreadid0,NULL,pthreadfunc1,&data0);
	data *pdata0;
	pthread_join(pthreadid0,(void **) &pdata0);//!!!!!!
	printf("num is %d in main\n",pdata0->num);

}
