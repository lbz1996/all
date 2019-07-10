#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
//指针常量和常量指针....
char* strFind(const char* sstring,const char* substring)
{
    assert(sstring != NULL && substring != NULL);
    int l0 = strlen(sstring);
    int l1 = strlen(substring);
    if(l0 < l1)
        return NULL;
    //先建立部分匹配表
    //"部分匹配值"就是"前缀"和"后缀"的最长的共有元素的长度。
    for(int i=0 ;i < l1 ;++i)
    {
        
    }
    int *pmTable = (int *) malloc(sizeof(int) * l1);
    memset(pmTable,0,sizeof(int) * l1);
    
    for(int i=0;i <= l0 - l1;++i)//.............!!!
    {
        int j = 0;
        for(; j< l1;++j)
        {
            if(sstring[i + j] != substring[j])
                break;
        }
        if(j == l1)
        {
            //return  (sstring + i);
            return (char*) (sstring + i);
        }
            //return const_cast<char*>(sstring + i);
    }
    return NULL;
}

int main()
{
    std::cout << "Hello world" << std::endl;
    char a1[] = "helloworld";
    char a2[] = "world";
    cout << strFind(a1,a2) << endl;
    char *a3 = strFind(a1,a2);

    *a3 = '0';
    cout << a1 << endl;

    return 0;
}

