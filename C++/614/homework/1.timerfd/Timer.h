#pragma once

#include <functional>
using namespace std;
namespace wd
{
class Timer
{
public:
    using TimerCallback = function<void()>;
    Timer(int initalTime,int intervalTime,TimerCallback &&cb)
    :_fd(createTimerfd())
    ,_initalTime(initalTime)
    ,_intervalTime(intervalTime)
    ,_cb(std::move(cb))
    ,_isStarted(false){}
    ~Timer() {}
    void start();
    void stop();
    void setTimer(int initTime,int intervalTime);
private:
    int createTimerfd();
    void handleRead();
private:
    int _fd;
    int _initalTime;
    int _intervalTime;
    TimerCallback _cb;
    bool _isStarted;

};
}
