#include <iostream>
#include <cstdio>
using namespace std;
void test1()
{
struct object
{
    char data[3];
};
    std::cout << "Hello world" << std::endl;
    //object obj_array[3] = {{'a','b','c'},{'d','e','f'},{'g','h','i'} };
    object obj_array[3] = { {'a','b','c'},{'d','e','f'},{'g','h','i'} };
    //.........
    object* cur = obj_array;
    printf("%c %c\n",*((char*)(cur) + 2),*((char*)(cur + 2)));
}
void test2()
{
    int a[4][5] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    printf("%d %d\n",*(&a[1]+1),*(a[1]+1));
}
int main()
{

    return 0;
}

