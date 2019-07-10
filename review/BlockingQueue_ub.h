#pragma once
#include "Mutex.h"
#include "Condition.h"
//#include <queue>
//using std::queue;
#include <boost/noncopyable.hpp>
#include <deque>
#include <assert.h>
namespace wd
{
template<typename T>
class ubBlockingQueue : boost::noncopyable
{
public:
    ubBlockingQueue() :_mutex() ,_notEmpty(_mutex) ,_queue() { }
    //~ubBlockingQueue() { }
    void push(T& x)
    {
        MutexLockGuard mutex(_mutex);
        _queue.push(x);
        _notEmpty.notify();
    }
    T pop()
    {
        MutexLockGuard mutex(_mutex);
        while(_queue.empty())
        {
            _notEmpty.wait();//会解锁并阻塞等待激活,锁被解开了--->另一个线程可以调用push而不会死锁
        }
        assert(_queue.empty());
        T x = _queue.front();
        _queue.pop_front();
        return x;
    }
    size_t size() const
    {
        //MutexLockGuard(_mutex);//......
        MutexLockGuard mutex(_mutex);
        return _queue.size();
    }
private:
    mutable MutexLock _mutex;//不加也不报错....
    Condition _notEmpty;
    std::deque<T> _queue;
};


}
