#include <iostream>
using namespace std;
int main()
{
    std::cout << "Hello world" << std::endl;
    int ival=1.01;
    int &rvall=1.01;
    int &rval2=ival;
    int &rval3;
//类型不可以对不上
//引用必须初始化,且类型一致(除了????和???)
    return 0;
}

