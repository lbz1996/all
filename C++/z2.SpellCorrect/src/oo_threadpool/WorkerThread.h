 ///
 /// @file    WorkerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-10 15:17:22
 ///

#pragma once

#include "Thread.h"
#include <iostream>
using namespace std;

namespace wd
{

class Threadpool;//防止发生头文件的循环引用
class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool & threadpool)
	: _threadpool(threadpool)
	{}

	~WorkerThread() {	cout << "~WorkerThread()" << endl;	}
private:
	void run();

private:
	Threadpool & _threadpool;
};

}//end of namespace wd
