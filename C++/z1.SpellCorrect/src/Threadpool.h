//线程池
//
#pragma once
#include "TaskQueue.h"
#include "Thread.h"
#include <vector>
#include <memory>
#include <functional>
#include <unistd.h>
using std::vector;
using std::unique_ptr;

namespace wd
{
//using Task = std::function<void()>;
class Threadpool
{

public:
    Threadpool(size_t threadNum,size_t queSize):_threadNum(threadNum),_queSize(queSize),_que(queSize),_isExit(false) 
    {
        _threads.reserve(_threadNum);//设置vector容量大小
    }
    //~Threadpool() {}
    void start()
    {
        for(size_t idx = 0;idx != _threadNum;++idx)
        {
            std::unique_ptr<Thread> thread(new Thread(std::bind(&Threadpool::threadFunc,this)));
            _threads.push_back(std::move(thread));
        }
        for(auto &thread:_threads)
            thread->start();
    }
    void stop()
    {
        if(!_isExit)
        {
            while(!_que.empty())
            {
                sleep(1);
            }
            _isExit = true;
            _que.wakeup();
            for(auto &thread:_threads)
                thread->join();
        }
    }
    void addTask(Task &&task)
    {
        _que.push(task);
    }
private:
    void threadFunc()
    {
        while(!_isExit)
        {
            Task task = getTask();
            if(task)
                task();
        }
    }
    Task getTask()
    {
        return _que.pop();
    }
private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _que;
    bool _isExit;
};


}
