 ///
 /// @file    WorkerThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-10 15:19:06
 ///
 
#include "WorkerThread.h"
#include "Threadpool.h"
namespace wd
{
void WorkerThread::run()
{
	_threadpool.threadFunc();
}
}//end of namespace wd
