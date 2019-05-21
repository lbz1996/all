#include <iostream>
using namespace std;
int main()
{
    std::cout << "Hello world" << std::endl;
    int a=11,b=2;
    int *pa=&a;
    cout<<*pa<<endl;
    *pa=88;
    cout<<a<<endl;
    pa=&b;
    cout<<*pa<<endl;

    return 0;
}

