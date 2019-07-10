#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    std::cout << "Hello world" << std::endl;
    string str1("hello\0world\0gg");
    char str2[] = "hello\0world\0gg\0";
    cout << "str1 is |" << str1 << endl; 
    cout << "str2 is |" << str2 << endl;
    printf("str1 print is |%s|\n",str1.c_str());
    printf("str2 print is |%s|\n",str2);
    return 0;
}

