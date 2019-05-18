#include<stdio.h>
#include<iostream>
#include<cstring>
using std::cin;
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(char *brand,double price):_price(price)
    {
        strcpy(_brand,brand);
    }
    void print()
    {
        printf("brand is %s,price is %lf\n",_brand,_price);
    }
    ~Computer()
    {

    }
private:
    char _brand[20];
    double _price;
};











