
#include "Threadpool.h"
#include <iostream>
#include <unistd.h>//!!!
using namespace std;
namespace  wd
{
void Threadpool::start()
{
    for(size_t idx = 0;idx != _threadNum;++idx)
    {
        unique_ptr<Thread> newone(new Thread( bind( &Threadpool::ThreadFunc,this )));
        _threads.push_back(move(newone));
    }
    for(auto &it:_threads)
        it->start();
}

void Threadpool::addTask(Task && task)
{
    _taskQue.push(move(task));
}
void Threadpool::stop()
{
    if(!_isExit)
    {
        while(!_taskQue.empty())
        {
            sleep(2);
        }
        _isExit = true;
        _taskQue.wakeup();
        for(auto &it:_threads)
            it->join();

    }
}
Task Threadpool::getTask()
{
    return _taskQue.pop();
}
void Threadpool::ThreadFunc()
{
    while(!_isExit)
    {
        Task task = getTask();
        if(task)
        {
            task();
        }
    }
}

}

