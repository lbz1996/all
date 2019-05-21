#include <iostream>
using namespace std;
int main()
{
    std::cout << "Hello world" << std::endl;
    int i=0,&r1=i;
    double d=0,&r2=d;

    r2=3.1;
    cout<<"r2 "<<r2<<endl;
    r2=r1;
    cout<<"r2 "<<r2<<endl;
    i=r2;
    cout<<"i "<<i<<endl;
    r1=d;
    cout<<"r1 "<<r1<<endl;

    return 0;
}

