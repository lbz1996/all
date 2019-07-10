#pragma once
#include "Macro.h"
#include "ThreadPool.h"
namespace wd
{
class Reactor
{
public:
    Reactor() {}
    ~Reactor() {}

private:
    ThreadPool _thread_pool;//线程池用来处理任务
};


}
