#include <iostream>
using std::cout;
using std::endl;
//C风格的类型转换
void test0()
{
    double number1=1.5;
    int number2=(int) number1;
    int number3=int(number1);
    cout<<number1<<endl
        <<number2<<endl
        <<number3<<endl;
}
void test1()
{
    double number1=1.5;
    int number2=static_cast<int>(number1);
    cout<<endl<<number1<<endl
        <<number2<<endl;
    int *pint=static_cast<int *> (malloc(sizeof(int)));
    *pint=1111;
    cout<<*pint<<endl;
    free(pint);
    //const_cast 去除常量属性                                          
    //dynamic_cast 在基类与派生类之间
    //reinterpret_cast 在任意类型之间进行转换 持久型？？？
}




int main()
{
    test0();
    test1();
    return 0;
}

