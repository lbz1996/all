#include <iostream>
using std::cout;
using std::endl;
int main()
{
    std::cout << "Hello world" << std::endl;
    double num1=1.11;
    //int num2=(int) num1;
    int num2=int(num1);//另一种转换方式
    cout<<num1<<endl;
    cout<<num2<<endl;
//4个关键字强制转换
//static_cast
    int num11=static_cast<int> (num1);
    cout<<num11<<endl;
    int *pint = static_cast<int *>(malloc(sizeof(int)));
    *pint=11;
    cout<<*pint<<endl;
//const_cast (const指针转非const指针)--去除常量属性
//dynamic_cast 基类和派生类之间转换
//reinterpert_cast 在任意类型之间进行转换 持久化操作?
//hanshuduijieshu?
    





    return 0;
}

