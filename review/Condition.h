#pragma once
#include "Mutex.h"
namespace wd
{

class Condition //---> 要配合锁mutex使用 ---> lock加锁,cond_wait等待前解锁,被signal/broadcast激活后又加锁,unlock解锁!!!
                //--->没进行错误检测......
{
public:
    Condition(MutexLock &mutex):_mutex(mutex) { pthread_cond_init(&_pcond,NULL); }
    ~Condition() { pthread_cond_destroy(&_pcond); }
    void wait()
    {
        pthread_cond_wait(&_pcond,_mutex.getPthreadMutex());
    }
    void notify()
    {
        pthread_cond_signal(&_pcond);
    }
    void notifyAll()
    {
        pthread_cond_broadcast(&_pcond);
    }
private:
    MutexLock& _mutex;
    pthread_cond_t _pcond;
};


}
