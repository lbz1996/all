#include <iostream>
#include <ctime>
#include <string>
using namespace std;
namespace wd
{

class CostTime
{
public:
    //CostTime() = delete;
    CostTime(const string &func): _start_time( clock() ), _func(func) {  }
    void begin(const string &func)
    {
        _start_time = clock();
        _func = func;
    } 
    void end()
    {
        _end_time = clock();
        cout << _func << " cost" <<(double)(_end_time - _start_time) / CLOCKS_PER_SEC <<"s"<<endl;
    }
private:
    time_t _start_time;
    time_t _end_time;
    string _func;
};

}

