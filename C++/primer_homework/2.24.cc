#include <iostream>

int main()
{
    std::cout << "Hello world" << std::endl;
    int i = 42;
    void *p = &i;
    long *lp = &i;//int 无法转换成long
    return 0;
}

