#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

class String
{
public:
    String();
    String(const char *pstr);
    String(const String&rhs);
    String & operator=(const String &rhs);
    ~String();
    void print();
private:
    char *_pstr;
};
void String::print()
{
    printf("%p:",&_pstr);
    printf("%s\n",_pstr);
}
String::~String()
{
    printf("析构函数\n");
    delete []_pstr;
}

String::String()
{
    printf("1\n");
    _pstr= new char[20]();
    strcpy(_pstr,"233");
}
String::String(const char *pstr)
{
    printf("2\n");
    _pstr= new char[20]();
    strcpy(_pstr,pstr);
}
String::String(const String &rhs)
{
    printf("3\n");
    _pstr=new char[20]();
    strcpy(_pstr,rhs._pstr);
}
String & String::operator=(const String &rhs)
{
    printf("4\n");
    if(this==&rhs)
        return *this;//为啥要加括号?
    delete []_pstr;
    _pstr=new char [20]();
    if(NULL!=_pstr)//else???
        strcpy(_pstr,rhs._pstr);
    return (*this);
}



int main()
{
    String str1;
    str1.print();
    //为啥不是24啊....
    String str2="Hello,world";
    str2.print();

    String str3("wangdao");
    str3.print();

    String str4=str3;
    str4.print();

    str4=str2;
    str4.print();

    return 0;
}












