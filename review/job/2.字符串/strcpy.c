#include <stdio.h>
#include <string.h>
#include <assert.h>
void func()
{
    char s[2] = {0};
    strcpy(s,"aaa");
}
int main()
{
    int a = 1;
    //assert(a == 0);
    func();
    return 0;
}

