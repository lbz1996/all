#include <iostream>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
using namespace std;
class MutexLock
{
public:
    static MutexLock* init()
    {
        if(_pMutexLock==nullptr)
        {
            _pMutexLock=new MutexLock();
        }
        //cout<<"inited"<<endl;
        return _pMutexLock;
    }
    static void destory()
    {
        if(_pMutexLock!=nullptr)
        {
            delete _pMutexLock;
        }
    }
    void print() const
    {
        cout<<"print:flag is "<<flag<<endl;
    }
    void lock()
    {
        if(1==flag)
        {
            while(1==flag);
        }
        flag=1;
        cout<<"print:flag is "<<flag<<endl;
    }
    void unlock()
    {
        if(0==flag)
        {
            while(0==flag);
        }
        flag=0;
        cout<<"print:flag is "<<flag<<endl;
    }
private:
    MutexLock()
    {
        cout<<"构造函数"<<endl;
        //memset(_pMutexLock,0,sizeof(MutexLock));
    }
    ~MutexLock()
    {
        cout<<"析构函数"<<endl;
    }
private:
    static MutexLock* _pMutexLock;
    int flag;
};
MutexLock* MutexLock::_pMutexLock=nullptr;



void* pthreadfunc(void *p)
{
    cout<<"in"<<endl;
    MutexLock *pmx=MutexLock::init();
    while(1)
    {
        pmx->lock();
        pmx->print();
        cout<<"i am 子线程"<<endl;
        pmx->unlock();
        sleep(1);
    }
    pthread_exit(NULL);
}



int main()
{
    pthread_t pthread_id;
    MutexLock *pm1=MutexLock::init();
    pm1->MutexLock::print();
    pthread_create(&pthread_id,NULL,pthreadfunc,nullptr);
    while(1)
    {
        pm1->lock();
        pm1->print();
        cout<<"i am 主线程"<<endl;
        pm1->unlock();
        sleep(1);
    }
    return 0;
}

