//pthread_cond
//->线程同步,pthread_cond_t类型作为区分
//->有线程等待条件变量条件成立而挂起,有线程使条件成立(给出条件成立信号)
//->为防止竞争,和 互斥锁 结合在一起
//
//成功返回0,失败返回非0
//pthread_cond_init
//pthread_cond_destory
//pthread_cond_wait
//pthread_cond_timedwait
//pthread_cond_signal
//pthread_cond_broadcast
//
//流程
//初始化
//自己pthread_mutex_lock->上锁
//自己pthread_cond_wait->解锁,本线程挂起阻塞
//外部pthread_cond_signal->线程继续执行,上锁
//自己pthread_mutex_unlock->解锁
//销毁
//在任务队列中对锁操作
#pragma once
#include "Noncopyable.h"
#include "MutexLock.h"
namespace wd
{

class Condition
: Noncopyable
{

public:
    Condition(MutexLock &mutex):_mutex(mutex) 
    {
        if(pthread_cond_init(&_cond,NULL))
            perror("pthread_cond_init");
    }
    ~Condition() 
    {
        if(pthread_cond_destroy(&_cond))
            perror("pthread_cond_destroy");
    }
    void Wait()
    {
        if(pthread_cond_wait(&_cond ,_mutex.ReturnMutexPtr()))
            perror("pthread_cond_wait");
    }
    void Notify()
    {
        if(pthread_cond_signal(&_cond))
            perror("pthread_cond_signal");
    }
    void NotifyAll()
    {
        if(pthread_cond_broadcast(&_cond))
            perror("pthread_cond_broadcast");
    }
private:
    pthread_cond_t _cond;
    MutexLock & _mutex;
};


}
