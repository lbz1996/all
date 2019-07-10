#include <iostream>
#include <cstdio>
using namespace std;
union student
{
    int i;
    char ch[2];
};
int main()
{
    std::cout << "Hello world" << std::endl;
    student s0;
    s0.i = 0x1420;
    printf("%d %d\n",s0.ch[0],s0.ch[1]);
    return 0;
}

