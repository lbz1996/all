#include "Thread.h"
#include <stdio.h>
#include <errno.h>
#include <iostream>
using namespace std;
namespace wd
{
Thread::~Thread()
{
    if(_isRunning)
    {
        pthread_detach(_phid);
        _isRunning = false;
    }
    cout<<"~Thread"<<endl;
}
void Thread::start()
{
    if(pthread_create(&_phid,nullptr,ThreadFunc,this))//在这里进行了传参,传自己
    {
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}   
void Thread::join()
{
    if(_isRunning)
    {
        pthread_join(_phid,nullptr);
        _isRunning = false;
    }
}
void *Thread::ThreadFunc(void *cb)
{
    Thread *pthread = static_cast<Thread*>(cb);
    if(pthread)
        pthread->_cb();
    return nullptr;
}

}
