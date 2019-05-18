#include<stdio.h>
#include<string.h>
int main()
{
	char s[64];
	memset(s,0,sizeof(s));
	while(scanf("%s",s))
	{
		char sb[64];
		memset(sb,' ',sizeof(sb));
		strcpy(sb+64-strlen(s),s);
		printf("%s\n",sb);
	}
	return 0;
}
