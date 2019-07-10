#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
void removeDuplicates(char *str)
{
    if(str == NULL)
        return;
    int len = strlen(str);
    if(len < 2)
        return;
    bool bit[256];
    memset(bit,false,sizeof(bit));
    int tail = -1;
    for(int i = 0 ;i<len ;++i)
    {
        if( !bit[ (int) str[i] ] )
        {
            bit[ (int) str[i] ] = true;
            ++tail;
            str[tail] = str[i];
        }
    }
    str[tail + 1] = 0;
}
int main()
{
    std::cout << "Hello world" << std::endl;
    char a[] = "abcd";
    removeDuplicates(a);
    cout << a << endl;
    char b[] = "aaaaabcd";
    removeDuplicates(b);
    cout << b << endl;
    return 0;
}

