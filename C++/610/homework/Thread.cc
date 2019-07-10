#include "Thread.h"
#include <iostream>
#include <errno.h>
namespace wd
{
using std::cout;
using std::endl;
Thread::~Thread()
{
    if(_is_running)
    {
        pthread_detach(_pthid);//与join不同,进行分离,主线程不阻塞
        _is_running = false;
    }
    cout<<"~Thread()"<<endl;
}

void Thread::start()
{
    if(pthread_create(&_pthid,nullptr,ThreadFunc,this))
    {
        perror("pthread_create");
        return;
    }
    _is_running = true;
}

void Thread::join()
{
    if(_is_running)
    {
        pthread_join(_pthid,nullptr);
        _is_running = false;
    }
}

void * Thread::ThreadFunc(void * arg)
{
    Thread * pthread = static_cast<Thread*>(arg);
    if(pthread)
        pthread->run();
    return nullptr;
}


}

