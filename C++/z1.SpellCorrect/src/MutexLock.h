//pthread_mutex
//线程互斥,控制对共享资源的获取
//pthread_mutex_t类型作为区分
//
//成功返回0,失败返回非0值  
//pthread_mutex_init
//pthread_mutex_destory
//pthread_mutex_lock
//pthread_mutex_unlock
//pthread_mutex_trylock
//
//死锁->多个线程(进程)因争夺资源而互相等待....
//->线程在加锁后解锁前被取消,锁将永远保持锁定状态(自己加锁自己要解锁...)
#pragma once
#include "Noncopyable.h"
#include <cstdio>
#include <iostream>
#include <errno.h>
#include <pthread.h>
using std::cout;
using std::endl;
namespace wd
{

class MutexLock
:Noncopyable
{
public:
    MutexLock():_isLocking(false)
    {
        if( pthread_mutex_init(&_mutex ,NULL) )
            perror("pthread_mutex_init");
    }
    ~MutexLock()
    {
        if( pthread_mutex_destroy(&_mutex) )
            perror("pthread_mutex_destroy");
    }
    void Lock()
    {
        if(pthread_mutex_lock(&_mutex))
        {
            perror("pthread_mutex_lock"); 
            return;
        }
        _isLocking = true;
    }
    void Unlock()
    {
        if(pthread_mutex_unlock(&_mutex))
        {
            perror("pthread_mutex_unlock");//成功返回0,失败返回非0值 
            return;
        }
        _isLocking = false;
    }
    pthread_mutex_t *ReturnMutexPtr(){ return &_mutex; }
private:
    bool _isLocking;//有啥用???
    pthread_mutex_t _mutex;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex):_mutex(mutex)
    {
        _mutex.Lock();
    }
    ~MutexLockGuard()
    {
        _mutex.Unlock();
    }
private:
    MutexLock &_mutex;
};



}
