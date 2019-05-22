#ifndef __HEAD_H__
#define __HEAD_H__
#include<iostream>
using namespace std;

//公有接口
class Line_out
{
public:
    Line_out(int,int,int,int);
    ~Line_out();
    void print() const;
private:
    class Line_in;
    Line_in *_p;
};

#endif
