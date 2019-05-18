#include <iostream>
namespace mine
{
void add(int x,int y)
{
    std::cout<<x+y<<std::endl;
}

}
int main()
{
    std::cout << "Hello world" << std::endl;
    using mine::add;
    add(2,22); 
    return 0;
}

