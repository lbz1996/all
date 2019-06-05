#include <iostream>
using namespace std;

template<typename T,int num = 10>
class Queue
{
private:
    T _save[num];
    int _begin;
    int _end;
    int _size;
public:
    Queue():_begin(-1),_end(-1),_size(0){}
    int size() { return _size; }
    bool empty(){return _size; }
    void pop()
    {
        if(_size)
        {
            --_size;
            _begin = (_begin+1)%num;
        }
        else
            cout<<"Queue is already empty"<<endl;
    }
    void push(const T one)
    {
        if(_size<num)
        {
            _end = (_end+1)%num;
            if(_size == 0)
                _begin = (_begin+1)%num;
            _save[_end] = one;
            ++_size;
        }
        else
            cout<<"Queue is already full"<<endl;
    }
    T top()
    {
        if(_size)
            return _save[_begin];
        cout<<"Queue is empty"<<endl;
        return NULL;
    }
};


int main()
{
    Queue<int,20> q0;
    q0.empty();
    for(int i=0;i<100;i+=3)
        q0.push(i);
    while(q0.empty())
    {
        cout<<q0.top()<<" ";
        q0.pop();
    }
    cout<<endl;
    return 0;
}





