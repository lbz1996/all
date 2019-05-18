#include<stdio.h>
int main()
{
	int k,num;
	scanf("%d",&k);
	int maxsum=0,currtsum=0;
	for(int i=0;i<k;++i)
	{
		scanf("%d",&num);
		currtsum+=num;	
		if(currtsum>maxsum)
			maxsum=currtsum;
		else if(currtsum<=0)
			currtsum=0;
	}
	printf("%d\n",maxsum);
	return 0;
}
