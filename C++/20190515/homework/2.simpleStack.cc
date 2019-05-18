#include <iostream>
#include <cstring>
using namespace std;

class stack
{
public:
    static stack* init()
    {
        if(p_stack==nullptr)
        {
            p_stack=new stack;
        }
        return p_stack;
    }
    static void destroy()
    {
        if(p_stack!=nullptr)
        {
            delete p_stack;
        }
    }
    void print() const
    {
        cout<<this<<": ";
        for(auto i:array)
            cout<<i<<" ";
        cout<<endl;
    }
    void push(int in)
    {
        if(top_idx>=10)
        {
            cout<<"应该程序终止....."<<endl;
        }
        else
        {
            array[++top_idx]=in;
        }
    }
    void pop()
    {
        if(-1==top_idx)
            cout<<"栈中没有元素"<<endl;
        else
        {
            array[top_idx--]=0;//还是就--?
        }
    }
    int top()
    {
        return array[top_idx];//程序终止.....
    }
    bool empty()
    {
        if(0==top_idx)
            return true;
        else
            return false;
    }
    bool full()
    {
        if(9==top_idx)
            return true;
        else
            return false;
    }
private:
    stack()
    {
        cout<<"构造函数"<<endl;
        memset(this,0,sizeof(stack));
        this->top_idx=-1;
    }
    ~stack()
    {
        cout<<"析构函数"<<endl;
    }

private:
    static stack *p_stack;
    int array[10];
    int top_idx;
};

stack * stack::p_stack=nullptr;




int main()
{
    stack *ps1=stack::init();
    ps1->push(10);ps1->print();
    ps1->push(12);ps1->print();
    ps1->push(14);ps1->print();
    cout<<ps1->top()<<endl;
    ps1->pop();   ps1->print();
    cout<<ps1->top()<<endl;
    stack *ps2=stack::init();
    ps2->print();
    return 0;
}

