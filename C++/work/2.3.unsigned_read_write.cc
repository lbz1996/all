#include <iostream>

int main()
{
    std::cout << "Hello world" << std::endl;
    unsigned u=10,u2=42;
    std::cout<<u2-u<<std::endl;
    std::cout<<u-u2<<std::endl;//无符号位计算不能出现负值
    int i=10,i2=42;
    std::cout<<i2-i<<std::endl;//其它按正常计算(先转换成无符号位)
    std::cout<<i-i2<<std::endl;
    std::cout<<i-u<<std::endl;
    std::cout<<u-i<<std::endl;
    return 0;
}

