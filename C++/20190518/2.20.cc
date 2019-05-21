#include <iostream>
using namespace std;
int main()
{
    std::cout << "Hello world" << std::endl;
    int i=42;
    int *p1=&i;

    cout<<*p1<<endl;
    *p1 = *p1 * *p1;
    cout<<*p1<<endl;

    return 0;
}

