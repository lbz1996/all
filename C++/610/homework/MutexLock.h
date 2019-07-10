#pragma once
#include "Nocopyable.h"
#include <stdio.h>
#include <errno.h>
#include <pthread.h>


namespace wd
{

class MutexLock
:Nocopyable
{
public:
    MutexLock():_is_locking(false)
    {
        if(pthread_mutex_init(&_mutex,NULL))
            perror("pthread_mutex_init");
    }
    ~MutexLock() 
    {
        if(pthread_mutex_destroy(&_mutex))
            perror("pthread_mutex_destroy");
    }
    void Lock()
    {
        if(pthread_mutex_lock(&_mutex))
            perror("pthread_mutex_lock");
        _is_locking = false;
    }
    void UnLock()
    {
        if(pthread_mutex_unlock(&_mutex))
            perror("pthread_mutex_unlock");
        _is_locking = true;
    }
    bool IsLocking() { return _is_locking; }
    pthread_mutex_t *GetMutexLockPtr() { return &_mutex; }
private:
    pthread_mutex_t _mutex;
    bool _is_locking; 
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &Mutex):_mutex(Mutex) { _mutex.Lock(); }
    ~MutexLockGuard(){ _mutex.UnLock(); }
private:
    MutexLock &_mutex;
};

}
