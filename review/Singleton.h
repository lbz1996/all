#pragma once
#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <cstdlib> //atexit
namespace wd
{

template<typename T>
class Singleton : boost::noncopyable
{
public:
    static T* GetInstance()
    {
        pthread_once(&_ponce,&Singleton::init);
        return *_pVal;
    }
private:
    Singleton() {}
    ~Singleton() {}
    static void init()
    {
        _pVal = new T();
        ::atexit(destory);//::???
    }
    static void destory()
    {
        delete _pVal;
    }
private:
    static pthread_once_t _ponce;
    static T* _pVal; 
};
template<typename T> 
pthread_once_t Singleton<T>::_ponce = PTHREAD_ONCE_INIT; //类模板
template<typename T> 
T* Singleton<T>::_pVal = NULL;

}
