#include "TaskQueue.h"
#include <iostream>
using namespace std;
namespace  wd
{
bool TaskQueue::full() const 
{
    return _que.size() == _queSize;
}
bool TaskQueue::empty() const 
{
    return _que.empty();//!!!
}
void TaskQueue::push(const ElemType &elem)
{
    {
        MutexLockGuard autolock(_mutex);
        while(full())
        {
            _notFull.wait();
        }
        _que.push(elem);
    }
    _notEmpty.notify();
}


ElemType TaskQueue::pop()
{
    MutexLockGuard autolock(_mutex);
    while(_flag && empty())
    {
        _notEmpty.wait();
    }
    if(_flag)
    {
        ElemType ret = _que.front();
        _que.pop(); 
        _notFull.notify();
        return ret;
    }
    else
    {
        return ElemType();//????
    }
}

void TaskQueue::wakeup()//干啥用的?
{
    if(_flag)
        _flag = false;
    _notEmpty.notifyAll();
}



}
