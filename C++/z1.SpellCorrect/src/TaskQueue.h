//任务队列
//主线程放任务,子线程取任务
//消费者-生产者模型
//通过pthread_cond控制
//两个条件变量
//满的时候任务不能加入队列
//空的时候任务不能从队列中取出
#pragma once
#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

namespace wd
{
using Task = std::function<void()>;
using ELemType = Task;//有啥意义???....
class TaskQueue
{

public:
    TaskQueue(size_t maxSize):_maxSize(maxSize),_mutex(),_notEmpty(_mutex),_notFull(_mutex),_flag(true) {}
    //~TaskQueue() {}
    bool empty() const { return _que.empty(); }
    bool full() const { return _que.size() == _maxSize; }
    void push(ELemType elem)//生产者线程
    {
        {
            MutexLockGuard autolock(_mutex);//利用构造函数自动上锁
            while(full())
            {
                _notFull.Wait();
            }
            _que.push(elem);
        }//利用析构函数自动解锁
        _notEmpty.Notify();
    }
    ELemType pop()//消费者线程
    {
        ELemType ret;
        {
            MutexLockGuard autolock(_mutex);
            while(_flag && empty())
            {
                _notEmpty.Wait();
            }
        }
        if(_flag)
        {
            ret = _que.front();
            _que.pop();
            _notFull.Notify();
        }
        else
            ret = nullptr;
        return ret;
    }
    void wakeup()//干啥用的?.....
    {
        _flag = false;
        _notEmpty.NotifyAll();
    }
private:
    size_t _maxSize;
    std::queue<ELemType> _que;
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
    bool _flag;//干啥用的...
};


}
