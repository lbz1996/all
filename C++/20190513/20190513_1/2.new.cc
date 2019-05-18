#include <iostream>
#include <cstdio>

int* a()
{
    int *p=new int(1);
    *p=998;
    printf("%p is %d\n",p,*p);
    return p;
}



int main()
{
    std::cout << "Hello world" << std::endl;
    int *p=a();
    printf("%p is %d\n",p,*p);
    return 0;
}

