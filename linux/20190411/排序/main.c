#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define L 10
#define R 100
void HeapSort(int *in,int length);
void print(int *in,int length)
{	
	for(int i=0;i<L;++i)
		printf("%d ",in[i]);
	printf("\n");
}
void init(int *in,int length)
{
	srand(time(NULL));
	for(int i=0;i<L;++i)
		in[i]=rand()%R;
}
int main()
{
	int in[L];
	init(in,L);
	print(in,L);
	HeapSort(in,L);
	print(in,L);
}

