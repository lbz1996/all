#include <iostream>
using namespace std;
int main()
{
    int i,&ri=i;
    i=5;
    cout<<"i "<<i<<" "<<"ri"<<ri<<endl;
    ri=10;
    cout<<"i "<<i<<" "<<"ri"<<ri<<endl;
    return 0;
}

