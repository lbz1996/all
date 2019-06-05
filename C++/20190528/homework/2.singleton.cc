#include<iostream>
using namespace std;

template<class T>
class Singleton
{
public:
    template<typename ...Args>
    static T *getInstance(Args... args)
    {
        if(nullptr == _p)
            _p = new T(args...);
        return _p;
    }
    static void destroy()
    {
        if(_p)
            delete _p;
    }
    void print()
    {
        cout<<"print()"<<endl;
    }
private:
    Singleton(){}
    ~Singleton(){}
private:
    static T *_p;
};

template<typename T>
T * Singleton<T>::_p = nullptr;

class Point
{
public:
    Point():_x(0),_y(0){cout<<"Point(0)"<<endl;}
    Point(int x,int y):_x(x),_y(y){cout<<"Point(2)"<<endl;}
    ~Point(){cout<<"~Point()"<<endl;}
    void print() { cout<<"("<<_x<<","<<_y<<")"<<endl; }
private:
    int _x;
    int _y;
};

class Point2
{
public:
    Point2():_x(0),_y(0),_z(0){cout<<"Point2(0)"<<endl;}
    Point2(int x,int y):_x(x),_y(y){cout<<"Point(2)"<<endl;}
    Point2(int x,int y,int z):_x(x),_y(y),_z(z){cout<<"Point2(3)"<<endl;}
    ~Point2(){cout<<"~Point2()"<<endl;}
    void print() { cout<<"("<<_x<<","<<_y<<","<<_z<<")"<<endl; }
private:
    int _x;
    int _y;
    int _z;
};

void t1()
{
    Point *p1 = Singleton<Point>::getInstance();
    p1->print();
    Point2 *p3 = Singleton<Point2>::getInstance(2,2);
    p3->print();
    p1->print();
}
void t2()
{
    Point *p2 = Singleton<Point>::getInstance(1,2);
    p2->print();
    Point2 *p4 = Singleton<Point2>::getInstance(2,3,4);
    p4->print();
    p2->print();

}
int main()
{
    //t1();
    t2();
    return 0;
}












