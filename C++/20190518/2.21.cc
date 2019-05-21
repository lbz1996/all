#include <iostream>
using namespace std;
int main()
{
    int i=0;
    int *pi=&i;
    //指针要同类型的
    double *pd=&i;
    int *pp=i;
    
    cout<<*pd<<" "<<*pi<<" "<<*pp<<endl;

    return 0;
}

