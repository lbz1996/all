#include<stdio.h>
int main()
{
	int k;
	scanf("%d",&k);
	int num,fnum,lnum;
		int bf,bl; 
	int maxsum=0,currtsum=0;
	int flag=1;//1代表需要更新fnum,0代表不需要
	for(int i=0;i<k;++i)
	{
		scanf("%d",&num);
		currtsum+=num;
		if(currtsum>maxsum)
		{
			maxsum=currtsum;
			if(flag)
			{
				bf=fnum;
				bl=lnum;
				fnum=num;
				flag=0;
			}
			lnum=num;
		}
		else if(currtsum==maxsum&&fnum<bf&&lnum<bl)
		{
			bf=fnum;
			bl=lnum;
		}
		else if(currtsum<=0)
		{
			currtsum=0;
			flag=1;
		}
	}
	printf("%d %d %d\n",maxsum,fnum,lnum);
	return 0;
}
