#include<stdio.h>
#include<unistd.h>
int main()
{
	char buf[32];
	printf("input string:");
	fgets(buf,sizeof(buf),stdin);
	fprintf(stdout,"the string is %s:",buf);
	return 0;
}
