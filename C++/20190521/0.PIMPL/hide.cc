#include "head.h"

class Line_out::Line_in
{
    class _point//public???
    {
    public:
        _point(int x=0,int y=0):__x(x),__y(y){}//=0初始化,少了参数默认就是0......:
        ~_point(){}
        void printPoint() const
        {
            cout<<"("<<__x<<","<<__y<<")";
        }
    private:
        int __x;
        int __y;
    };
public:
    Line_in(int x1=0,int y1=0,int x2=0,int y2=0):point1(x1,y1),point2(x2,y2){}
    ~Line_in(){cout<<"~Line_in"<<endl;}
    void printLine_in() const
    {
        point1.printPoint();
        cout<<"------>";
        point2.printPoint();
        cout<<endl;
    }
private:
    _point point1;
    _point point2;
};



//inline有啥区别......
inline Line_out::Line_out(int x1,int y1,int x2,int y2)
:_p(new Line_in(x1,y1,x2,y2)){}

inline Line_out::~Line_out()
{
    if(_p)
        delete _p;
}

inline void Line_out::print() const
{
    _p->printLine_in();
}







