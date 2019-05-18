#include <iostream>
#include <stdio.h>
using namespace std;//using bianyi zhiling
//using shiti quanbuyiru
using std::endl;//using sheng ming jizhi  using xiandingfu
namespace wd
{
int number=10;
void display()
{
    cout<<"display()"<<endl;

}
void cout()
{
    printf("hello world\n");
}
}//end of namespace wd
using namespace wd;
int main()
{
    display();
    wd::cout();
    return 0;
}//
