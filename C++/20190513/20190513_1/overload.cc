#include <iostream>
//C++支持函数重载
//原理:名字改编(name mangling)
//操作步骤:当函数名称相同时,根据函数的参数的类型,顺序,个数进行改编
//进行改编的函数按照C++的方式进行调用
//
//
//
//
//不进行名字改编:按照C的方式进行调用
extern "C"
{
    int add(int x ,int y)
    {
        return x+y;
    }

}//end of extern "C"
int add(int x,int y, int z)
{
    return x+y+z;
}
double add(double x,int y, int z)
{
    return x+y+z;
}
int main()
{
    printf("Hello world\n");
    int a=3,b=4;
    double c=5.1111;
    printf("%d\n",add(a,b));
    printf("%lf\n",add(c,b,a));
    return 0;
}

