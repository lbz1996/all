#include "TimerThread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <functional>
using namespace std;
struct Mytask
{
    void process()
    {
        srand(time(NULL));
        int number = rand() % 100;
        cout<<"thread "<<pthread_self()<<" get number "
            <<number<<endl;
    }
};
int main()
{
    wd::TimerThread timer(1,6,bind(&Mytask::process,Mytask()));
    timer.start();
    sleep(20);
    timer.stop();
    while(1);
    return 0;
}

