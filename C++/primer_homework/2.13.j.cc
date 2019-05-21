#include <iostream>
using namespace std;

int i=100;
int main()
{
    std::cout << "Hello world" << std::endl;
    int i=42;
    int j=i;
    cout<<j<<endl;
    j=::i;//显式的访问全局变量i
    cout<<j<<endl;
    return 0;
}

