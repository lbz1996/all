#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
//观察者模式(发布/订阅模式)
// (抽象!)主题/通知者(subject)             抽象观察者(observer)
// (具体!)主题/通知者(concrete subject)    具体观察者(concrete observer)
 
class Observer;

class Subject
{
public:
    virtual void add(Observer *) = 0;
    virtual void remove(Observer *) = 0;
    virtual void notify() const = 0;
    virtual ~Subject() {  }
};

class Observer
{
public:
    virtual void update() = 0;//推拉模式//推的话,通知者保留观察者列表,自己主动推送   
    virtual ~Observer() {  }            //拉的话,观察者保留通知者列表,自己负责获取
};                                      //所以不同模式二者保留的东西不一样,,,,,

class ConcreteSubject1
:public Subject
{
public:
    void add(Observer * p_Observer)
    {
        if(_p_ConcreteObserver1.end() == find(_p_ConcreteObserver1.begin(),_p_ConcreteObserver1.end(),p_Observer))
            _p_ConcreteObserver1.push_back(p_Observer);
        else
            cout<<p_Observer<<" is already added"<<endl;
    }
    void remove(Observer * p_Observer)
    {
        list<Observer*>::iterator it = find(_p_ConcreteObserver1.begin(),_p_ConcreteObserver1.end(),p_Observer);
        if(_p_ConcreteObserver1.end() != it)
            _p_ConcreteObserver1.erase(it);
        else
            cout<<p_Observer<<" doesn`t exist"<<endl;
    }
    void notify() const
    {
        cout<<"ConcreteSubject1 begin notify"<<endl;
        for(auto &it:_p_ConcreteObserver1)//&
            it->update();
    }
private:
    list<Observer*> _p_ConcreteObserver1;
    //list<Observer*> _p_ConcreteObserver2;
    //...
};

class ConcreteObserver1
:public Observer
{
public:
    ConcreteObserver1(const string &name):_name(name) {  }
    ConcreteObserver1():_name("无名") {  }
    void update()
    {
        cout<<"ConcreteObserver1: "<<_name<<" is notified"<<endl;
    }
private:
    string _name;
};


int main()
{
    unique_ptr<Observer> pOB0( new ConcreteObserver1() );
    unique_ptr<Observer> pOB1( new ConcreteObserver1("OB1") );
    unique_ptr<Observer> pOB2( new ConcreteObserver1("OB2") );
    ConcreteSubject1 CS1;
    CS1.add(pOB0.get());
    CS1.add(pOB0.get());
    CS1.add(pOB1.get());
    CS1.add(pOB2.get());
    CS1.notify();
    CS1.remove(pOB0.get());
    CS1.notify();
    CS1.remove(pOB0.get());
    return 0;
}

