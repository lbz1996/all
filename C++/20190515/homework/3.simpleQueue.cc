#include <iostream>
#include <cstring>
using namespace std;

class queue
{
public:
    static queue* init()
    {
        if(_p_queue==nullptr)
            _p_queue=new queue();//写不写括号有啥区别???
        return _p_queue;
    }
    static void destroy()
    {
        if(_p_queue!=nullptr)
            delete _p_queue;//这里加不加括号.......
    }
    void print() const
    {
        cout<<this<<": ";
        for(int i:_array)
            cout<<i<<" ";
        cout<<endl;
    }
    void push(int in)
    {
        cout<<"入队: "<<in<<endl;
        if(0==_node_nums)
        {
            cout<<"此时队列为空"<<endl;
            _array[_back_idx]=in;
            ++_node_nums;
        }
        else if(10==_node_nums)
        {
            cout<<"此队列已满"<<endl;
        }
        else
        {
            _back_idx=(_back_idx+1)%11;
            _array[_back_idx]=in;
            ++_node_nums;
        }
    }
    void pop()
    {
        if(0==_node_nums)
            cout<<"队列空,没东西能出来"<<endl;
        else
        {
            cout<<"出队: "<<_array[_front_idx]<<endl;
            _array[_front_idx]=0;
            _front_idx=(_front_idx+1)%11;
            --_node_nums;
        }
    }
    int front()
    {
        return _array[_front_idx];
    }
    int back()
    {
        return _array[_back_idx];//不管合法......
    }
    bool empty()
    {
        if(0==_node_nums)
            return true;
        else
            return false;
    }
    bool full()
    {
        if(10==_node_nums)
            return true;
        else
            return false;
    }

private:
    queue()
    {
        cout<<"构造函数"<<endl;
        memset(this,0,sizeof(queue));
    }
    ~queue()
    {
        cout<<"析构函数"<<endl;
    }
private:
    static queue *_p_queue;
    int _array[10];
    int _front_idx;
    int _back_idx;
    int _node_nums;
};

queue *queue::_p_queue=nullptr;

int main()
{
    queue *pq1=queue::init();
    pq1->push(14); pq1->print();
    pq1->push(16); pq1->print();
    cout<<pq1->front()<<endl;
    cout<<pq1->back()<<endl;
    pq1->pop(); pq1->print();
    queue *pq2=queue::init();
    pq2->push(18); pq2->print();

    return 0;
}

