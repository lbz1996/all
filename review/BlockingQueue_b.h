#pragma once
#include "Mutex.h"
#include "Condition.h"
#include <assert.h>
#include <boost/noncopyable.hpp>
#include <boost/circular_buffer.hpp>
//#include <deque>
namespace wd
{

template<typename T>
class bBlockingQueue : boost::noncopyable
{
public:
    //deque构造函数...
    bBlockingQueue(size_t maxSize):_mutex(),_notEmpty(_mutex),_notFull(_mutex),_deque(maxSize) {  }
    //~bBlockingQueue() {}
    void push(T& x)
    {
        MutexLockGuard mutex(_mutex);
        while(_deque.full())
        {
            _notFull.wait();
        }
        assert(_deque.full());
        _deque.push(x);
        _notEmpty.notify();
    }
    T pop()
    {
        MutexLockGuard mutex(_mutex);
        while(_deque.empty())
        {
            _notFull.wait();
        }
        assert(_deque.empty());
        T x = _deque.front();
        _deque.pop_front();
        _notFull.notify();
        return x;
    }
    bool empty() const 
    {
        MutexLockGuard mutex(_mutex);
        return _deque.empty();
    }
    bool full() const 
    {
        MutexLockGuard mutex(_mutex);
        return _deque.full();
    }
    size_t size() const
    {
        MutexLockGuard mutex(_mutex);
        return _deque.size();
    }
    size_t capacity() const
    {
        MutexLockGuard mutex(_mutex);
        return _deque.capacity();
    }
private:
    mutable MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
    //std::deque<T> _deque; //......
    boost::circular_buffer<T> _deque;
};


}
