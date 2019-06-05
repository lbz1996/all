#include <iostream>
#include <cmath>
using namespace std;

class Circle
{
public:
    Circle():_radius(0.0){ }
    Circle(double r):_radius(r){ }

    double getArea() { return _radius * _radius; }
    double getPerimeter() { return 2*M_PI*_radius; }
    void show()
    {
        cout<<"Circle show()"<<endl;
        cout<<"Area is "<<getArea()<<endl;
        cout<<"Perimeter is "<<getPerimeter()<<endl;
    }

private:
    double _radius;
};

class Cylinder
{

};









int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

