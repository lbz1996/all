#include <iostream>
#include <memory>
#include <cmath>
using namespace std;


class Figure
{
public:
    virtual void display() const = 0;
    virtual double area() const = 0;
    virtual ~Figure() { cout<<"~Figure()"<<endl; }
};

class Rectangle
:public Figure
{
public:
    Rectangle(size_t length,size_t width):_length(length),_width(width) { }
    ~Rectangle(){ cout<<"~Rectangle()"<<endl; }
    void display() const { cout<<"Rectangle display()"<<endl; }
    double area() const { return _length * _width; }
private:
    size_t _length;
    size_t _width;
};

class Circle
:public Figure
{
public:
    Circle(double radius):_radius(radius) {  }
    ~Circle() { cout<<"~Circle()"<<endl; }
    void display() const { cout<<"Circle display()"<<endl; }
    double area() const { return 3.14 * _radius * _radius; }
private:
    double _radius;
};


//静态(简单)工厂
//还可以通过参数不同调用不同的构造
class SimpleFactory
{
public:
    static Figure * CreateRectangle() { return new Rectangle(1,1); }
    static Figure * CreateCircle() { return new Circle(3); }
};
//工厂方法模式(一对一)
class Factory
{
public://!!!!
    virtual Figure * create() = 0;
    virtual ~Factory() {  }
};
class RectangleFactory
: public Factory
{ 
public:
    Figure * create() { return new Rectangle(1,1); }
};
class CircleFactory
:public Factory
{
public:
    Figure * create() { return new Circle(3); }
};

class Line;
//抽象工厂模式
class AbstractFactory
{
public:
    static Figure* createFigure();
    static Line* createLine();
    virtual ~AbstractFactory() {  }
};

class Line
{
public:
    virtual void display() const =0;
    virtual ~Line() {  }
};

class SLine
:public Line
{
public:
    SLine(double x = 0,double y = 0):_x(x),_y(y) {  }
    void display() const { cout<<"SLine"<<endl; }
private:
    double _x;
    double _y;
};

class AbstractFactory1
:public AbstractFactory
{
public:
    Figure *createFigure() { return new Rectangle(1,1); }
    Line *createLine() { return new SLine(); }
};

class AbstractFactory2
:public AbstractFactory
{
public:
    Figure *createFigure() { return new Circle(3); }
    Line *createLine() { return new SLine(2,2); }
};


int main()
{
    cout<<"静态(简单)工厂模式"<<endl;
    unique_ptr<Figure> rectangle( SimpleFactory::CreateRectangle() );
    unique_ptr<Figure> circle( SimpleFactory::CreateCircle() );
    rectangle->display();//unique_ptr有get函数返回自己的值
    circle->display();
    cout<<"工厂模式"<<endl;
    unique_ptr<Factory> f1(new RectangleFactory());//unique
    unique_ptr<Figure>  rec(f1->create());
    rec->display();
    unique_ptr<Factory> f2(new CircleFactory());//unique
    unique_ptr<Figure>  cir(f2->create());
    cir->display();
    cout<<"抽象工厂模式?..."<<endl;

    unique_ptr<AbstractFactory1> abf1;
    unique_ptr<AbstractFactory2> abf2;
    unique_ptr<Figure> rec1(abf1->createFigure());
    rec1->display();
    unique_ptr<Line> l1(abf1->createLine());
    l1->display();
    unique_ptr<Figure> rec2(abf2->createFigure());
    rec2->display();
    unique_ptr<Line> l2(abf1->createLine());
    l2->display();

    return 0;
}

