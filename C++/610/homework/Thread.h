#pragma once
#include "Nocopyable.h"
#include <pthread.h>
#include <functional>
namespace wd
{
class Thread 
:Nocopyable
{
    using ThreadCallback = std::function<void()>;
public:
    //面向对象
    //Thread():_pthid(0),_is_running(false) {}
    //基于对象
    Thread(ThreadCallback &&func):_pthid(0),_is_running(false),run(std::move(func)) {}//!!!
    ~Thread();
    void start();
    void join();
private:
    static void* ThreadFunc(void *);
    //面向对象
    //virtual void *run() = 0;
private:
    pthread_t _pthid;
    bool _is_running;
    //基于对象
    ThreadCallback run;
};
}




