#include <iostream>
#include <cstdio>
using namespace std;
//atexit+静态方法



class Singleton
{
public:
    static Singleton *getInstance()
    {
        if(nullptr==_pSingleton)
        {
            _pSingleton = (Singleton *) new Singleton();
            atexit(destory);
        }
        return _pSingleton;
    }
    void print() {cout<<"print()"<<endl;}
    static void destory()
    {
        if(_pSingleton)
            delete  _pSingleton;
    }
private:
    Singleton(){cout<<"构造函数"<<endl;}
    ~Singleton(){cout<<"析构函数"<<endl;}
private:
    static Singleton *_pSingleton;
};

//Singleton *Singleton::_pSingleton = nullptr;
Singleton *Singleton::_pSingleton = getInstance();
//二者区别.....

int main()
{
    Singleton *p = Singleton::getInstance();
    p->print();
    return 0;
}

