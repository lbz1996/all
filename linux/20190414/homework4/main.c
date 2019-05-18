#include<stdio.h>
#include<unistd.h>
int main()
{
	execl("./add","add","3","4",NULL);
	return 0;
}
