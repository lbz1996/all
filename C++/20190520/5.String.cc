#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class String
{
public:

    String():_pstr(nullptr){}

    String(const char *str)
    {//初始化不应该管_pstr吧.....
        _pstr = (char*) malloc(strlen(str));
        strcpy(_pstr,str);
        //cout<<c_str()<<endl;
    }

    String(const String &str1)//const??
    {
        //String &str2 = const_cast<String&>(str1);
        this->_pstr = (char*) malloc(str1.size());
        strcpy(_pstr,str1.c_str());
    }

    ~String()
    {
        if(_pstr)
        {
            cout<<"~String"<<endl;
            free(_pstr);
        }
        else
            cout<<"空string"<<endl;
    }
    void print()
    {
        cout<<_pstr<<endl;
    }

    String &operator=(const String &str)
    {
        if(this==&str)
            return (*this);
        if(_pstr)
            free(_pstr);
        //String &str2 = const_cast<String&>(str);
        //this->_pstr = (char*) malloc(strlen(str2.c_str()));
        //strcpy(_pstr,str2.c_str());
        this->_pstr = (char*) malloc(str.size());//这里为啥就不报错????
        strcpy(_pstr,str.c_str());
        return (*this);
    }

    String &operator=(const char* str)
    {
        if(_pstr)
            free(_pstr);
        _pstr = (char*) malloc(strlen(str));
        strcpy(_pstr,str);
        return *this;//加不加括号有啥区别啊????
    }

    String &operator+=(const String &str)
    {
        //String &str2 = const_cast<String&>(str);//const?????.....!!!!!
        char *str0 = (char*) malloc(size());
        strcpy(str0,_pstr);
        _pstr = (char*) malloc(size()+str.size());
        sprintf(_pstr,"%s%s",str0,str.c_str());
        return *this;
    }

    String &operator+=(const char *str)
    {
        char *str0 = (char*) malloc(strlen(_pstr));
        strcpy(str0,_pstr);
        _pstr = (char*) malloc(strlen(_pstr)+strlen(str));
        sprintf(_pstr,"%s%s",str0,str);
        return *this;
    }

    char &operator[](std::size_t index)
    {
        static char nznull = '\0';//31
        if(index<size())//>=0always true
            return _pstr[index];
        else
        {
            cout<<"下标越界"<<endl;
            return nznull;
        }
    }
    const char &operator[](std::size_t index) const
    {
        static char nznull = '\0';//31
        if(index<size())//>=0always true
            return _pstr[index];
        else
        {
            cout<<"下标越界"<<endl;
            return nznull;
        }
    }

    std::size_t size() const
    {
        return strlen(_pstr);
    }

    const char* c_str() const//......
    {
        return _pstr;
    }

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char *_pstr;
};

String operator+(const String &str1, const String &str2)
{
    String s3;
    s3=str1;
    s3+=str2;
    return s3;
}
String operator+(const String &str1, const char *str2)
{
    String s3;
    s3=str1;
    s3+=str2;
    return s3;
}
String operator+(const char *str1, const String &str2)
{
    String s3;
    s3=str1;
    s3+=str2;
    return s3;
}

bool operator==(const String &str1, const String &str2)
{
    if(0==strcmp(str1.c_str(),str2.c_str()))
        return true;
    else
        return false;
}
bool operator!=(const String &str1, const String &str2)
{
    if(0==strcmp(str1.c_str(),str2.c_str()))
        return false;
    else
        return true;
}

bool operator<(const String &str1, const String &str2)
{
    if(0>strcmp(str1.c_str(),str2.c_str()))
        return true;
    else
        return false;
}
bool operator>(const String &str1, const String &str2)
{
    if(0<strcmp(str1.c_str(),str2.c_str()))
        return true;
    else
        return false;
}
bool operator<=(const String &str1, const String &str2)
{
    if(0>=strcmp(str1.c_str(),str2.c_str()))
        return true;
    else
        return false;
}
bool operator>=(const String &str1, const String &str2)
{
    if(0<=strcmp(str1.c_str(),str2.c_str()))
        return true;
    else
        return false;

}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    //os<<"s is "<<s.c_str()<<endl;
    os<<s.c_str()<<endl;
    return os;
}
std::istream &operator>>(std::istream &is, String &s)
{
    string s0;//......
    is>>s0;
    s=s0.c_str();
    return is;
}

void test1()
{
    String s1("gogogo");
    s1.print();

    String s2(s1);
    s2.print();

    s2="lalala";
    s2.print();

    String s3=s2;
    s3.print();

    s3+="ohohoh";
    s3.print();

    s3+=s1;
    s3.print();

    for(size_t i=0;i!=strlen(s3.c_str());++i)
        cout<<s3[i];
    cout<<endl;
}
void test2()
{
    String s0="|string|";
    String s1=s0+s0; s1.print();
    String s2=s0+"|char*|"; s2.print();
    String s3="|char*|"+s0; s3.print();
}
void test3()
{
    String s0="abcdef";
    String s1="abc";
    cout<<(s0==s1)<<endl;
    cout<<(s0!=s1)<<endl;
    cout<<(s0<s1)<<endl;
    cout<<(s0>s1)<<endl;
    cout<<(s0<=s1)<<endl;
    cout<<(s0>=s1)<<endl;
}
void test4()
{
    String s0;
    cin>>s0;
    cout<<s0;
}
int main()
{
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}

