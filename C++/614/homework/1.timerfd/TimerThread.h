#pragma once
#include "Timer.h"
#include "Thread.h"
namespace  wd
{
class TimerThread
{
    using TimerCallback = function<void()>;
public:
    TimerThread(int initTime,int intervalTime,TimerCallback &&cb)
    :_timer(initTime,intervalTime,std::move(cb))
    ,_thread(bind(&Timer::start,&_timer))//Timer的bind作为Thread的_cb被其ThreadCallback调用
    {}
    void start()
    {
        _thread.start();//pthread_create->ThreadFunc->_cb
    }
    void stop()
    {
        _timer.stop();
        //_timer的文件描述符应该关闭
        //ll /proc/进程号/fd  查看文件描述符
        _thread.join();
    }
    ~TimerThread() {}

private:
    Timer _timer;
    Thread _thread;
};


}
