#include <iostream>

#include <log4cpp/Category.hh>

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

//#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>

#include <log4cpp/Priority.hh>

using namespace std;
using namespace log4cpp;

#define prefix(msg) string (msg).append(__FUNCTION__).append(__FILE__).append(to_string(__LINE__))

class Mylogger
{
public:
    static Mylogger *GetInstance()
    {
        cout<<"GetInstance"<<endl;
        if(nullptr==_p_Mylogger)
        {
            _p_Mylogger=new Mylogger();
        }
        return _p_Mylogger;
    }
    static void destroy()
    {
        cout<<"destroy()"<<endl;
        if(nullptr!=_p_Mylogger)
        {
            delete _p_Mylogger;
        }
        else
            cout<<"_p_Mylogger is nullptr"<<endl;
    }
    template<typename ...Args>
    void warn(string formate,Args... args)
    {
        //_record.setPriority(Priority::WARN);
        char msg[1000]={0};
        sprintf(msg,formate.c_str(),args...);
        _record.warn(msg);
    }


private:
    Mylogger():_record(Category::getRoot().getInstance("这是种类的名字?有啥用?"))
    {
        PatternLayout * _patternLayout1;
        PatternLayout * _patternLayout2;

        OstreamAppender *_outAppender;
        FileAppender *_fileAppender;
        cout<<"构造函数"<<endl;
        _patternLayout1 =new PatternLayout();
        _patternLayout1->setConversionPattern("%d %c %x:%m%n");
        _patternLayout2 =new PatternLayout();
        _patternLayout2->setConversionPattern("%d %c %x:%m%n");

        _outAppender=new OstreamAppender("这个是显示的目的地名字???",&cout);
        _outAppender->setLayout(_patternLayout1);

        _fileAppender=new FileAppender("这是显示的目的地的名字?在程序中的名字???","这是保存的文件名???");
        _fileAppender->setLayout(_patternLayout2);

        _record.setAppender(_outAppender);
        _record.addAppender(_fileAppender);
    }
    ~Mylogger()
    {
        cout<<"析构函数"<<endl;
        Category::shutdown();
    }
private:
    static Mylogger *_p_Mylogger;


    Category &_record;
};
Mylogger *Mylogger::_p_Mylogger=nullptr;



void test1()
{
    Mylogger *m1 = Mylogger::GetInstance();
    m1->warn("test%d()\n",1);
}


int main()
{
    Mylogger *m1 = Mylogger::GetInstance();
    m1->warn("%d %c %s %p\n",1,'c',"hello",m1);
    test1();
    Mylogger::destroy();
    return 0;
}

