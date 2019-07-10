#pragma once
#include <boost/noncopyable.hpp>
#include <assert.h>
#include <pthread.h>
namespace wd
{
class MutexLockGuard;//类前声明
class Condition;
class MutexLock
{
public:
    //Mutex():_holder(0) { pthread_mutex_init(&_mutex,NULL); }
    MutexLock():_holder(0) 
    { 
        pthread_mutexattr_t mutexAttr;
        pthread_mutexattr_init(&mutexAttr);
        pthread_mutexattr_settype(&mutexAttr,PTHREAD_MUTEX_NORMAL);

        pthread_mutex_init(&_mutex,&mutexAttr); 

        pthread_mutexattr_destroy(&mutexAttr);
    }
    ~MutexLock() { assert(_holder == 0); pthread_mutex_destroy(&_mutex); }
    //bool isLockedByThisPthread() { return _holder == CurrentThread::tid(); }
    //void assertLocked() { assert(isLockedByThisPthread()); }
//private:
//    friend wd::MutexLockGuard;
//    friend wd::Condition;
    //顺序???
    void lock()//仅供MutexLockGuard调用
    {
        pthread_mutex_lock(&_mutex);
        //_holder = CurrentThread::tid();
    }
    void unlock()//仅供MutexLockGuard调用
    {
        _holder = 0;
        pthread_mutex_unlock(&_mutex);
    }
    pthread_mutex_t* getPthreadMutex()//用处??? 仅供Condition调用,严禁用户代码调用
    {
        return &_mutex;
    }
private:
    pthread_mutex_t _mutex;
    pid_t _holder;//持有的线程???
};

class MutexLockGuard//运用MutexLockGuard的生命周期,通过构造函数和析构函数自动完成加锁解锁(Scoped Locking 范围锁)
{
public:
    //显式调用
    explicit MutexLockGuard(MutexLock &mutex):_mutex(mutex) 
    { 
        _mutex.lock();
    }
    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};
//防止遗漏变量名,直接产生一个临时对象又马上被销毁了,结果没有锁住临界区
#define MutexLockGuard(x) static_assert(false,"missing mutex guard var name");

}
