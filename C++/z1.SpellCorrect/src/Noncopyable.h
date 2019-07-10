#pragma once
namespace wd
{
//C++ primer p440
//定义阻止拷贝的类->将拷贝构造函数和拷贝赋值运算符定义为删除的函数( =delete  )
//拷贝构造函数的第一个参数必须是引用类型
//->用来初始化非引用类型参数->而非引用类型参数在函数调用中会进行拷贝初始化
//->所以自己的参数必须是引用类型,否则会无限循环!
class Noncopyable
{
public:
    Noncopyable() {}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable &) = delete; 
    Noncopyable &operator= (const Noncopyable &) = delete;
};

}
