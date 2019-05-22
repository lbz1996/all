#include <iostream>
#include <cstdio>
#include <pthread.h>
using namespace std;
//atexit+pthread_once



class Singleton
{
public:
    static Singleton * getInstance()
    {
        pthread_once(&_once,init);
        return _pSingleton;
    }
    void print() const {cout<<"print()"<<endl;}
    static void init()
    {
        _pSingleton = new Singleton();
        ::atexit(destory);
    }
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
    static pthread_once_t _once;
};

Singleton *Singleton::_pSingleton = nullptr;
pthread_once_t Singleton::_once =PTHREAD_ONCE_INIT; 

int main() 
{ 
    Singleton *p = Singleton::getInstance();
    p->print();
    return 0;
}

