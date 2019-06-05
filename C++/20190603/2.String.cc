#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
class String
{
public:
    String(const char *str)
    :_pstr(new char[strlen(str)+1])//()是否初始化
    {
        cout<<"String(char *str)"<<endl;
        strcpy(_pstr,str);
    }
    String(const String &rhs)//复制构造函数
    :_pstr(new char[strlen(rhs._pstr)+1] ())
    {
        cout<<"String(const String &rhs)"<<endl;
        strcpy(_pstr,rhs._pstr);
    }
    String(String &&rhs)//移动构造函数,右值引用作为标志
    :_pstr(rhs._pstr)//浅拷贝
    {
        cout<<"String(String &&rhs)"<<endl;
        rhs._pstr = nullptr;
    }

    String &operator=(const String &rhs)
    {
        cout<<"String &operator=(const String &rhs)"<<endl;
        if(rhs._pstr != _pstr)//避免自复制
        {
            delete []_pstr;   //[]调用析构函数
            _pstr = new char[strlen(rhs._pstr)+1] ();
            strcpy(_pstr,rhs._pstr);
        }
        return *this;
    }
    String &operator=(String &&rhs)
    {
        cout<<"String &operator=(const String &&rhs)"<<endl;
        if(rhs._pstr != _pstr)//避免自复制
        {
            delete []_pstr;   //[]调用析构函数
            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
        }
        return *this;
    }
    ~String()
    {
        cout<<"~String()"<<endl;
        if(_pstr)
            delete [] _pstr;
    }

private:
    char *_pstr;
};







int main()
{
    std::cout << "Hello world" << std::endl;
    String str0("hello");
    String str1 = "world";
    str1 = "gg";
    String str2(move(str0));
    return 0;
}

