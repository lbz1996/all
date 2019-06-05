#include <iostream>
using namespace std;
//单例模式
//通过某个类只能创建出一个对象<-所以对象创建在堆上
//不能在栈上，全局静态区上（为啥不可以？？？）
//替换场景：累死C中全局变量的作用
//static作用
//https://www.cnblogs.com/songdanzju/p/7422380.html 
//内部存储布局
//https://blog.csdn.net/u014470361/article/details/79297601
//主要是static

class Singleton
{
public:
    static Singleton *GetInstace()
    {
        if(_pSingleton == nullptr)
            _pSingleton = new Singleton();
        return _pSingleton;
    }
    static void destory()
    {
        if(_pSingleton)
            delete _pSingleton;
    }
    void print()
    {
        cout<<_pSingleton<<endl;
    }
private:
    Singleton() { cout<<"Singleton()"<<endl; }
    ~Singleton() { cout<<"~Singleton()"<<endl; }
private:
    static Singleton *_pSingleton;
};

Singleton *Singleton::_pSingleton = nullptr;






int main()
{
    std::cout << "Hello world" << std::endl;
    //Singleton s0;
    Singleton *s1 = Singleton::GetInstace();
    s1->print();
    Singleton *s2 = Singleton::GetInstace();
    s2->print();
    Singleton::destory();
    return 0;
}

