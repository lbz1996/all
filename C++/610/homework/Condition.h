#pragma once
#include "Nocopyable.h"
#include "MutexLock.h"
#include "pthread.h"
namespace wd
{
class Condition
:Nocopyable
{
public:
    Condition(MutexLock &mutex):_mutex(mutex)
    {
        if(pthread_cond_init(&_cond,nullptr))
            perror("pthread_cond_init");
    }
    ~Condition()
    {
        if(pthread_cond_destroy(&_cond))
            perror("pthread_cond_destroy");
    }
    void wait()
    {
        if(pthread_cond_wait(&_cond,_mutex.GetMutexLockPtr()))
            perror("pthread_cond_wait");
    }
    void notify()
    {
        if(pthread_cond_signal(&_cond))
            perror("pthread_cond_signal");
    }
    void notifyAll()
    {
        if(pthread_cond_broadcast(&_cond))
            perror("pthread_cond_broadcast");
    }

private:
    //引用不是对象没有生命周期
    MutexLock & _mutex;//const??
    pthread_cond_t _cond;
};


}
