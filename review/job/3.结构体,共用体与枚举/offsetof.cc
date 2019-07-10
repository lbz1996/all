#include <iostream>
#include <cstdlib>
using namespace std;
struct record
{
    int a;
    char b;
    short c;
};

int main()
{
    std::cout << "Hello world" << std::endl;
    record r0;
    r0.a = 273;
    cout << offsetof(record,a) << endl;
    cout << offsetof(record,b) << endl;
    cout << offsetof(record,c) << endl;
    return 0;
}

