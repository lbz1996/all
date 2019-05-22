#include <iostream>
using namespace std;



//类嵌套类+静态对象
class Singleton
{
    class _AutoRealseSingleton
    {
    public:
        _AutoRealseSingleton(){cout<<"_AutoRealseSingleton"<<endl;}
        ~_AutoRealseSingleton()
        {
            cout<<"~_AutoRealseSingleton"<<endl;
            if(_pSingleton)
                delete _pSingleton;
        }

    };
public:
    static Singleton *getInstance()
    {
        if(nullptr==_pSingleton)
            _pSingleton = (Singleton *) new Singleton();
        return _pSingleton;
    }
    void print() {cout<<"print()"<<endl;}
    //deatory......
private:
    Singleton(){cout<<"构造函数"<<endl;}
    ~Singleton(){cout<<"析构函数"<<endl;}
    friend class _AutoRealseSingleton; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
private:
    static Singleton *_pSingleton;
    static _AutoRealseSingleton __pAutoRealseSingleton;
};


Singleton::_AutoRealseSingleton Singleton::__pAutoRealseSingleton;
Singleton *Singleton::_pSingleton = nullptr;



int main()
{
    Singleton *p = Singleton::getInstance();
    p->print();
    return 0;
}

