#include<stdio.h>
void print()
{
	for(int i=0;i<10;++i)
		printf("%d\n",i);
}
int main()
{
	int in[10];
	print();
	in[11]=29;
	return 0;
}
