//多线程pthread
//pthread_create -> 确定相应调用的线程函数的入口点?
//pthread_join -> 正常资源不会随着线程结束被释放
//             -> 而join可以时调用的线程阻塞至被等待线程结束为止,且会回收被等待资源的线程
//pthread_exit
#pragma once
#include "Noncopyable.h"
#include <pthread.h>
#include <functional>
#include <iostream>
namespace wd
{

class Thread
{
public:
    using ThreadCallback = std::function<void()>;
    //p470
    //右值引用+std::move
    Thread(ThreadCallback && cb):_pthid(0),_cb(std::move(cb)),_isRunning(false) { }
    void start()
    {
        pthread_create(&_pthid,NULL,_threadFunc,this);//this
        _isRunning = true;
    }
    void join()//调用join的是主线程,不是_pthid代表的线程
    {
        if(_isRunning)
            pthread_join(_pthid,NULL);
    }
    ~Thread() 
    {
        if(_isRunning)
            pthread_detach(_pthid);//分离
    }
private:
    static void *_threadFunc(void *arg)//_threadFunc里面调用cb......
    {                                  //传过来的是this
        Thread * pthread = static_cast<Thread*>(arg);
        if(pthread)
            pthread->_cb();
        return nullptr;
    }
private:
    pthread_t _pthid;
    ThreadCallback _cb;
    bool _isRunning;
};


}
