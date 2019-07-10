#include "Timer.h"
#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <iostream>
using namespace std;
namespace wd
{
void Timer::start()
{
    _isStarted = true;
    setTimer(_initalTime,_intervalTime);
    struct pollfd pfd;
    //struct pollfd {
    //    int   fd;         /* file descriptor */
    //    short events;     /* requested events */
    //    short revents;    /* returned events */

    //};
    pfd.fd = _fd;
    pfd.events = POLLIN;
    while(_isStarted)
    {
        int nready = ::poll(&pfd,1,5000);
        //轮询事件集,时间个数,非阻塞/阻塞/固定时间阻塞  
        //成功返回准备就绪个数
        //0表示超时后没有文件描述符准备好
        //-1表示出错了
        if(nready == -1 && errno == EINTR)//中断信号
            continue;
        else if(nready == -1)
        {
            perror("poll");
            return ;
        }
        else if(nready == 0)
        {
            cout<<"poll timeout"<<endl;
        }
        else
        {
            if(pfd.revents && POLLIN)
            {
                handleRead();
                //处理读事件,否则会一直触发(水平/边缘?)
                if(_cb)
                    _cb();
            }
        }

    }
}
void Timer::stop()
{
    if(_isStarted)
    {
        setTimer(0,0);
        //文件描述符还在,不会被关闭
        _isStarted = false;
    }
}
int Timer::createTimerfd()
{
    int fd = timerfd_create(CLOCK_REALTIME,0);
    if(fd == -1)
    {
        perror("timerfd_create");
    }
    return fd;
}   
void Timer::setTimer(int initalTime,int intervalTime)
{
    struct itimerspec value;
    value.it_value.tv_sec = initalTime;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = intervalTime;
    value.it_interval.tv_nsec = 0;
    int ret = timerfd_settime(_fd,0,&value,nullptr);
    if(-1 == ret)
        perror("timerfd_settime");
}
void Timer::handleRead()
{
    uint64_t howmany;
    int ret = read(_fd,&howmany,sizeof(howmany));
    if(ret != sizeof(howmany))
        perror("read");
}   



}
