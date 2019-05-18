#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class singleton
{
public:
    static singleton * GetInstance(int key)
    {
        if(p_singleton==nullptr)
        {
            p_singleton=new singleton(key); 
        }       
        return p_singleton;
    }
    static void destroy()
    {
        cout<<"destroy()"<<endl;
        if(p_singleton!=nullptr)
        {
            delete p_singleton;
        }
        else
            cout<<"p_singleton is nullptr"<<endl;
    }
    void print() const
    {
        cout<<"key is "<<key<<endl;
    }

private:
   static singleton *p_singleton;
   int key;
   singleton(int in)
   {
        key=in;
        cout<<"构造函数"<<endl;
   }
   ~singleton()
   {//destory里面的delete还是会调用析构函数
       cout<<"析构函数"<<endl;
   }
};
singleton *singleton::p_singleton=nullptr;



int main()
{
    singleton *s1=singleton::GetInstance(1);
    singleton *s2=singleton::GetInstance(2);
    singleton *s3=singleton::GetInstance(3);
    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
    s1->print();//都是1,if只进入了一次
    s2->print();
    s3->print();
    s1->destroy();
    s2->destroy();
    s3->destroy();
    return 0;
}














