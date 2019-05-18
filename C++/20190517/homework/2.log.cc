#include <iostream>

#include <log4cpp/Category.hh>

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

//#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>

#include <log4cpp/Priority.hh>

using namespace std;
using namespace log4cpp;



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
    void warn(const char *msg)
    {
        _record.setPriority(Priority::WARN);
        char str[200]={0};
        sprintf(str,"msg is %s, filename is %s, func is %s,line is %d",msg,__FILE__,__func__,__LINE__);
        _record.warn(str);
    }


private:
    Mylogger():_record(Category::getRoot().getInstance("这是种类的名字?有啥用?"))
    {
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

    PatternLayout * _patternLayout1;
    PatternLayout * _patternLayout2;

    OstreamAppender *_outAppender;
    FileAppender *_fileAppender;

    Category &_record;
};
Mylogger *Mylogger::_p_Mylogger=nullptr;



void test1()
{
    Mylogger *m1 = Mylogger::GetInstance();
    m1->warn("test1");

}


int main()
{
    Mylogger *m1 = Mylogger::GetInstance();
    m1->warn("main");
    test1();
    return 0;
}

