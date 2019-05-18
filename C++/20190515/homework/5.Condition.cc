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
    }
    void unlock()
    {
        if(0==flag)
        {
            while(0==flag);
        }
        flag=0;
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


class Conditon
{
public:
    static Conditon* init()
    {
        if(_pCondition==nullptr)
        {
            _pCondition=new Conditon();
        }
        return _pCondition;
    }
    static void destory()
    {
        if(_pCondition!=nullptr)
        {
            delete _pCondition;
        }
    }
    void getMutex(MutexLock *in)
    {
        _pMutexLock=in;
    }
    void wait()
    {
        while(0==flag);
        _pMutexLock->lock();
        if(1==flag)
        {
            flag=0;
            _pMutexLock->unlock();
        }
        else
        {
            --flag;
            _pMutexLock->unlock();
        }
    }
    void notify()
    {
        _pMutexLock->lock();
        flag=1;
        _pMutexLock->unlock();
    }
    void notifyall()
    {
        _pMutexLock->lock();
        flag=2;
        _pMutexLock->unlock();
    }
private:
    Conditon()
    {
        cout<<"构造函数"<<endl;
        //memset(_pMutexLock,0,sizeof(MutexLock));
        flag=0;
    }
    ~Conditon()
    {
        cout<<"析构函数"<<endl;
    }
private:
    static Conditon* _pCondition;
    int flag;
    MutexLock *_pMutexLock;
};
Conditon* Conditon::_pCondition=nullptr;






void* pthreadfunc(void *p)
{
    MutexLock *pmx=MutexLock::init();
    Conditon *pcd=Conditon::init();
    pcd->getMutex(pmx);
    while(1)
    {
        pcd->wait();
        cout<<"i am 子线程"<<*((int*)p)<<endl;
        sleep(1);
    }
    pthread_exit(NULL);
}



int main()
{
    MutexLock *pm1=MutexLock::init();
    pm1->MutexLock::print();
    Conditon *pcd=Conditon::init();
    pcd->getMutex(pm1);

    int id1=1;
    pthread_t pthread_id1;
    pthread_create(&pthread_id1,NULL,pthreadfunc,(void *) &id1);
    int id2=2;
    pthread_t pthread_id2;
    pthread_create(&pthread_id2,NULL,pthreadfunc,(void *) &id2);

    while(1)
    {
        cout<<"i am 主线程"<<endl;
        //pcd->notify();
        pcd->notifyall();
        sleep(3);
    }
    return 0;
}

