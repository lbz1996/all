#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
void replaceFunc(char str[],int length)
{
    int spaceCount = 0;
    for(int i = 0;i<length;++i)
    {
        if(str[i] == ' ')
            ++spaceCount;
    }
    int newlength = length + spaceCount * 2;
    for(int i = 0;i<length;++i)
    {
        
    }
}
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

