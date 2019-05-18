#include <iostream>
#include <cstdio>
using std::cout;
using std::endl;
//内联函数
//宏定义容易出错(如算符优先级)
//解决:多加括号....
//     使用内联函数

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

