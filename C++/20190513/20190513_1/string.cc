#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
int main()
{
    std::cout << "Hello world" << std::endl;
    char str[]="hello,world";
    const char *pstr="hello,world";
    string s1="hello";
    string s2("world");//什么函数?构造函数?
    string s3=s1+s2;
    cout<<s3<<endl;
    //for(size_t idx=0;idx!=s2.size();++idx)
    //{
    //    cout<<s2[idx]<<endl;
    //}
    s2.append(",zhenshen");
    for(char i:s2)
    {
        cout<<i;
    }
    cout<<endl;
    //截取字串
   //查找
    size_t idx=s3.find("e");
    string s4=s3.substr(idx,8);
    cout<<s4<<endl;
    return 0;
}

