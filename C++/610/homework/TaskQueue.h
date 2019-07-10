#pragma once
#include "MutexLock.h"
#include "Condition.h"
#include <queue>
//基于对象
#include <functional>
using std::queue;
using std::function;

namespace wd
{
//基于对象,任务队列中直接就是要注册调用的函数
using ElemType = function<void()>;
class TaskQueue
{
public:
    TaskQueue(size_t queSize = 10):_queSize(queSize),_que(),_mutex(),_notFull(_mutex),_notEmpty(_mutex),_flag(true) {}
    ~TaskQueue() {}
    bool full() const; 
    bool empty() const; 
    void push(const ElemType &elem);
    ElemType pop();
    void wakeup();
private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _flag;
};


}
