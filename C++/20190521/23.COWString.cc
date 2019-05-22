#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class String
{
public:

    String():_pstr(new char[1+4]()+4) { cout<<"String()"<<endl; initref(); }

    String(const char *str):_pstr(new char[strlen(str)+1+4] +4 )
    {
        cout<<"String(const char *str)"<<endl;
        initref();
        strcpy(_pstr,str);
    }

    String(const String &str1):_pstr(str1._pstr) { cout<<"String(const String &str1)"<<endl; addref(); }

    ~String() { release(); }//可以用~String替代realease嘛?

    void print() { cout<<_pstr<<":"<<*( (int*) (_pstr-4) )<<endl; }

    String &operator=(const String &str)
    {
        cout<<"operator ="<<endl;
        if(this!=&str)
        {
            release();
            _pstr = str._pstr;
            addref();//这里不能是const了,因为会改引用计数                    
                     //不对,调用自己的就完事了....
        }
        return (*this);
    }

    String &operator=(const char* str)
    {
        if(0!=strcmp(str,_pstr))
        {
            cout<<"operator ="<<endl;
            release();
            _pstr = new char[strlen(str)+1+4] + 4 ;
            initref();//这样引用计数会有bug
            strcpy(_pstr,str);
        }
        return *this;//加不加括号有啥区别啊????
    }

    String &operator+=(const String &str)
    {                                       
        if(0!=str.size())
        {
            cout<<"in"<<endl;
            char *ptmp = (char*) malloc(size());
            strcpy(ptmp,_pstr);
            //cout<<__LINE__<<endl;
            release();//不先存就释放有可能爆炸....
            //cout<<__LINE__<<endl;
            _pstr = new char[strlen(ptmp)+str.size()+1+4] + 4;
            initref();//这样引用计数会有bug
            sprintf(_pstr,"%s%s",ptmp,str.c_str());
            cout<<"out"<<endl;
        }
        return *this;
    }

    String &operator+=(const char *str)
    {
        if(0!=strlen(str))
        {
            char *ptmp = (char*) malloc(size());
            strcpy(ptmp,_pstr);
            release();//不先存就释放有可能爆炸....
            _pstr = new char[strlen(ptmp)+strlen(str)+1+4] + 4;
            initref();//这样引用计数会有bug
            sprintf(_pstr,"%s%s",ptmp,str);
        }
        return *this;
    }

    char &operator[](std::size_t index)//与int区别
    {
        cout<<"char &operator[]"<<endl;
        if(index<size())//>=0always true
        {
            if(showref()>1)
            {
                subref();
                char *ptmp = new char[size()+1+4] + 4;
                strcpy(ptmp,_pstr);
                _pstr = ptmp;
                initref();
            }
            return _pstr[index];
        }
        else
        {
            cout<<"下标越界"<<endl;
            static char nznull = '\0';//31
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


    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

    std::size_t size() const{ return strlen(_pstr); } 
    const char* c_str() const { return _pstr; }
    int showref(){return *( (int*) (_pstr-4) );}

private:
    void initref() { *( (int*) (_pstr-4) ) = 1; }
    void addref() { ++*( (int*) (_pstr-4) ); }
    void subref() { --*( (int*) (_pstr-4) ); }
    void release()
    {
        subref();
        if(0==showref())
        {
            delete [] (_pstr-4);//[]!!!!!!!!!!!!!!!
            cout<<"0==ref,so deleted"<<endl;
        }
    }
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
    if(s.size()!=0)
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
        cout<<s3[i]<<endl;
    cout<<endl;
    s3[s3.size()-1]='*';
    s3.print();
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
    cout<<__LINE__<<endl;
    cin>>s0;
    cout<<__LINE__<<endl;//之前的release是>>中的临时对象
    cout<<s0;
    cout<<__LINE__<<endl;
}
int main()
{
    test1();
    //test2();
    //test3();
    //test4();
    return 0;
}

