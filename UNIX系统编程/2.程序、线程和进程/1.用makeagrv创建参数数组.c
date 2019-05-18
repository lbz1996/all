#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int makegrv(const char *s,const char *delimitere,char ***argcvp)
{
	char *in=(char *) malloc(sizeof(s));
	strcpy(in,s);
	char *changed=strtok(in,delimitere);
	if(NULL==changed)
	{
		printf("wrong input\n");
		return -1;
	}
	printf("gg,%s\n",changed);
	char *out;
	while((out=strtok(NULL,delimitere))!=NULL)
	{
		printf("%s\n",out);
	}
	return 0;
}



