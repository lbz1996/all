#include <iostream>
using namespace std;
#ifdef __cplusplus
extern "C"
{
#endif
    int add(int x,int y)
    {
        return x+y;
    }
#ifdef __cplusplus
}
#endif

int add(int x ,int y, int z)
{
    return x+y+z;
}


int main()
{
    cout<<add(1,2)<<endl
        <<add(1,2,3)<<endl;
    return 0;
}

