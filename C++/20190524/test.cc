#include <iostream>
class A
{
public:
    A() { } 
private:
    int num;
};
class B : public A
{
public:
    B():A() { }
private:
    int  num2;
};


int main()
{
    std::cout << "Hello world" << std::endl;
    B b;
    B* pb = &b;
    return 0;
}

