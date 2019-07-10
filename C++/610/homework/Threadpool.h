#pragma once
#include "TaskQueue.h"
#include "Thread.h"
#include <memory>//!!!!!!
#include <vector>
#include <functional>
using namespace std;
namespace wd
{
using Task = function<void()>;
class Threadpool
{
    friend class WorkerThread;//???
public:
    Threadpool(size_t threadNum,size_t queSize)
    : _threadNum(threadNum),_queSize(queSize),_taskQue(queSize),_isExit(false)
    {_threads.reserve(_threadNum);}
    ~Threadpool() {}
    void start();
    void stop();
    void addTask(Task && task);
private:
    void ThreadFunc();
    Task getTask();
private:
    size_t _threadNum;
    size_t _queSize;
    vector< unique_ptr<Thread> >  _threads;
    TaskQueue _taskQue;
    bool _isExit;
};


}
