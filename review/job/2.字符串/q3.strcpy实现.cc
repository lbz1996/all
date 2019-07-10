#include <iostream>
#include <cstdio>
#include <cassert>
//#include <cstring>
#include <string.h>
using namespace std;
namespace my
{

char *strcpy(char *des,const char *res)
{
    assert(des != NULL && res != NULL);
    while( (*des++ = *res++) != '\0');
    return des;
}

}
void test1()
{
    char a[] = "helloworld"; 
    char b[] = "gogogo";
    my::strcpy(a,b);
    cout << a << endl;
}
void test2()
{
    char a[] = "helloworld"; 
    char b[] = "gogogo";
    //my::strcpy(b,a);
    strcpy(b,a);
    cout << b << endl;
    char c[2] = {0};
    strcpy(c,a);
    cout << c << endl;
}
int main()
{
    std::cout << "Hello world" << std::endl;
    //test1();
    test2();
    return 0;
}

