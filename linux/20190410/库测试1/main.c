#include "head.h"
//int myadd(int a,int b);
//int mymulti(int a,int b);
int main()
{
	int i,j;
	scanf("%d %d",&i,&j);
	printf("a + b is %d\n",myadd(i,j));
	printf("a *b is %d\n",mymulti(i,j));
#ifdef DEBUG
	printf("DEBUGGING\n");
#endif
	return 0;
}
