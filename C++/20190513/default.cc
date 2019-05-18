#include <iostream>
using std::cout;
using std::endl;


int add(int x,int y=0)
{
    return x+y;
}


int add(int x,int y=2,int z=3)
{
    return x+y+z;
}


int main()
{
    cout<<add(1,996)<<endl;//使用缺省参数的函数重载会造成二义性,会报错
    return 0;
}

