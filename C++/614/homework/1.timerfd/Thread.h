#pragma once
#include "Noncopyable.h"
#include <pthread.h>
#include <functional>
using namespace std;


namespace wd
{

class Thread
:Noncopyable
{
public:
    using ThreadCallback = function<void()>;
    Thread(ThreadCallback cb):_phid(0),_isRunning(false),_cb(cb){}
    ~Thread();
    void start();
    void join();
private:
    static void *ThreadFunc(void *);
private:
    size_t _phid;
    bool _isRunning;
    ThreadCallback _cb;
};


}
