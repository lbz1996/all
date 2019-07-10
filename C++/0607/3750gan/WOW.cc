#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <deque>
using namespace std;
namespace WOW
{
//weapon,warrior,city,path

//WOWconfig
class WOWconfig//单例,保留t组测试数据ConfigData
{
public:
    char warriors[5][20]={"dragon","ninja","iceman","lion","wolf"};
    char weapons[3][20]={"sword","bomb","arrow"};
    bool AllUsed() { return _currectID >= _maxID; }
    void AddID() { ++_currectID;}
    void ReadData();
    void SetData(int *M,int *N,int *K,int *T);
    static WOWconfig *GetInstance();
    static void Destory();
private:
    WOWconfig():_currectID(0){cout<<"WOWconfig"<<endl;}
    ~WOWconfig(){cout<<"~WOWconfig"<<endl;}

    class ConfigData//保留1组测试数据:M(指挥部生命),N(指挥部之间有几个城市city),K(lion每前进一步掉多少血), T(到T为止时发生的事件)
    {
    public:
        ConfigData(int M,int N,int K,int T):_M(M),_N(N),_K(K),_T(T){}
        int _M,_N,_K,_T;
    };
    static WOWconfig *_pWOWconfig;
    vector<ConfigData> _DataArray;
    int _currectID,_maxID;
};
WOWconfig * WOWconfig::_pWOWconfig = nullptr;
WOWconfig * WOWconfig::GetInstance()
{
    if(_pWOWconfig == nullptr)
        _pWOWconfig = new WOWconfig;
    return _pWOWconfig;
}
void WOWconfig::Destory()
{
    if(_pWOWconfig != nullptr)
        delete  _pWOWconfig;
}
void WOWconfig::ReadData()
{
    int M,N,K,T;
    cin>>_maxID;
    for(int i=0;i<_maxID;++i)
    {
        cin>>M>>N>>K>>T;
        _DataArray.push_back(ConfigData(M,N,K,T));
    }
}
void WOWconfig::SetData(int *M,int *N,int *K,int *T)
{
    if(!AllUsed())
    {
        AddID();
        *M = _DataArray[_currectID]._M;
        *N = _DataArray[_currectID]._N;
        *K = _DataArray[_currectID]._K;
        *T = _DataArray[_currectID]._T;
    }
}
//********************************************************************************************************
//Time 
class Time//单例,保留最大时间,保留调整当前时间,输出语句打印当前时间 
{
public:
    static Time *GetInstance();
    static void Destory();
    void SetTimeNow() { _timeNow += 5; }
    void SetTimeMax(int &&T) { _timeMax = T; }
    void print_time() { printf("%03d:%02d ",_timeNow/60,_timeNow%60); }
    int GetTimeNow(){ return _timeNow; }
private:
    Time():_timeNow(0) { cout<<"Time()"<<endl; }
    ~Time() { cout<<"~Time()"<<endl; }
private:
    static Time *_pTime;
    int _timeNow,_timeMax;
};
Time *Time::_pTime = nullptr;
Time *Time::GetInstance()
{
    if(_pTime == nullptr)
        _pTime = new Time;
    return _pTime;
}
void Time::Destory()
{
    if(_pTime != nullptr)
        delete  _pTime;
}
//********************************************************************************************************
//weapon
class weapon
{
public:
    weapon(int type):_type(type)
    {
        switch (type)
        {
        case 0:_use_time = -1;break;
        case 1:_use_time = 1;break;
        case 2:_use_time = 2;break;
        }
    }
    int show_type(){ return _type; }
    int show_use(){ return _use_time; }
    void set_use(int kase) { _use_time = kase; }//初始化,使用后调整
private:
    int _use_time;
    int _type;
};
//********************************************************************************************************
//warrior
#define PUSH_POP \
{\
    _weaponA[0].set_use(_weaponA[0].show_use() - 1);\
    if(_weaponA[0].show_use() > 0)\
    _weaponA.push_back(_weaponA[0]);\
    _weaponA.pop_front();\
}

class warrior
{
public:
    warrior(bool rb,int id,int type,int elements,int atk):_rb(rb),_id(id),_type(type),_elements(elements),_atk(atk),_can_go(1){}
    ~warrior(){}//cout<<"~warrior"<<endl;}

    int get_rb() { return _rb; }
    int get_id() { return _id; }
    int get_type() { return _type; }
    int get_elements(){ return _elements; }
    int get_atk() { return _atk; }

    void get_weapon(weapon weapon0) { if(_weaponA.size()<10) _weaponA.push_back(weapon0); }
    void show_weapon();
    int sort_weapon();//战斗前排序
    deque<weapon> *weapon_out(int num);
    int use_weapon(int enemy_atk);

    int get_harmed(int harmed) { is_changed = harmed; _elements -= harmed; return _elements; }
    void set_elements(int elements) { _elements = elements; };//???.....
int get_can_go() { return _can_go; } 
void set_can_go(bool can_go) { _can_go = can_go; }
public:
bool is_changed;
deque<weapon> _weaponA;
//vector<weapon> _weaponR;//......
private:
bool _rb;
int _id;
int _type;
int _elements;
int _atk;
bool _can_go;
};

void warrior::show_weapon()
{
    int out[3] = {0};
    for(size_t i=0;i<_weaponA.size();++i)
        ++ out[ _weaponA[i].show_type() ] ;
    print_time();
    printf("%s%s %d has %d sword %d bomb %d arrow and %d elements\n",RED_BLUE(_rb),warriors[_type],_id,out[0],out[1],out[2],_elements);
}

int warrior::use_weapon(int enemy_atk)
{
    int atk = _atk;
    if( _weaponA.size() )
    {
        switch (_weaponA[0].show_type())
        {
        case 0:
            _weaponA.push_back(_weaponA[0]);
            _weaponA.pop_front();
            return atk * 2/10; 
        case 1:
            PUSH_POP;
            if(_type != 1)//ninja
                _elements -= enemy_atk * 5/10;//敌人取整后的攻击力的1/2(去尾取整)......
            return atk * 4/10; 
        case 2:
            PUSH_POP;
            return atk * 3/10; 
        }
    }
    return 0;
}

bool cmp1(weapon weapon1,weapon weapon2) { return weapon1.show_type() < weapon2.show_type(); }
bool cmp2(weapon weapon1,weapon weapon2) { return weapon1.show_use() < weapon2.show_use(); }
bool cmp3(weapon weapon1,weapon weapon2) { return weapon1.show_use() > weapon2.show_use(); }
int warrior::sort_weapon()
{
    sort(_weaponA.begin(),_weaponA.end(),cmp1);//武器按编号从小到大排序
    deque<weapon>::iterator begin,end;
    for(deque<weapon>:: iterator it = _weaponA.begin();it != _weaponA.end();++it)
    {
        if(it->show_type() == 2)
        {
            begin = it;
            while(it->show_type() == 2)
                ++it;
            end = it;
            break;
        }
    }
    sort(begin,end,cmp2);//同一武器种类(arrow)用过的排在前面
    return _weaponA.size();
}
deque<weapon> *warrior::weapon_out(int num)
{
    if(_weaponA.size()!=0)
    {
        deque<weapon> *weapon_tmp = new deque<weapon>;//接收的负责删除...
        sort(_weaponA.begin(),_weaponA.end(),cmp1);
        int type = _weaponA[0].show_type();
        int num2=0;
        for(size_t i=0;i<_weaponA.size();++i)
            if(_weaponA[i].show_type() == type)
                ++num2;
            else
                break;
        sort(_weaponA.begin(),_weaponA.begin()+num2-1,cmp3);//用不用-1.....
        //num是准备拿的,num2是可以拿的
        num2 = num2 < num ? num2 : num;
        for(int i=0;i<num2;++i)
            weapon_tmp->push_back(_weaponA[i]);
        for(int i=0;i<num2;++i)
            _weaponA.pop_front();
        return weapon_tmp;
    }
    return nullptr;
}
//......
class dragon :public warrior 
{
public:
    dragon(bool rb,int id,int type,int elements,int atk):warrior(rb,id,type,elements,atk){}
};
class ninja :public warrior 
{
public:
    ninja(bool rb,int id,int type,int elements,int atk):warrior(rb,id,type,elements,atk){}

};
class iceman :public warrior 
{ 
public:
    iceman(bool rb,int id,int type,int elements,int atk):warrior(rb,id,type,elements,atk){}
    void elements__()//{ _elements -= _elements *1/10; }//........
    {set_elements(get_elements() - get_elements()*1/10);}//假设为当前//是减去的量要取整....
};
class lion:public warrior
{
public:
    lion(bool rb,int id,int type,int elements,int atk,int loyal):warrior(rb,id,type,elements,atk),_loyal(loyal){}
    int get_loyal(){return _loyal;}
    void loyal__() { _loyal -= K; }
private:
    int _loyal;
};
class wolf:public warrior 
{
public:
    wolf(bool rb,int id,int type,int elements,int atk):warrior(rb,id,type,elements,atk){}
};
#define DRAGON_YELL(w) \
{\
    if(0 == w->get_type())\
    {\
        print_time();\
        printf("%s%s %d yelled in city %d\n",RED_BLUE( w->get_rb() ),warriors[w->get_type()],w->get_id(),_id);\
    }\
}
//********************************************************************************************************
#define FIGHT_INSIDE1(w1,w2) \
    if(w1->_weaponA.size()!=0)\
{\
    w2->get_harmed(w1->use_weapon(w2->get_atk()));\
    if(w2->get_elements()<0)\
    {\
        print_time();\
        if(w1->get_elements()<0)\
        {\
            if(0 == w1->get_rb())\
            printf("both red %s %d and blue %s %d died in city %d\n",warriors[w1->get_type()],w1->get_id(), warriors[w2->get_type()],w2->get_id(),_id);\
            else\
            printf("both red %s %d and blue %s %d died in city %d\n",warriors[w2->get_type()],w2->get_id(), warriors[w1->get_type()],w1->get_id(),_id);\
            delete w1,w2;\
            w1 = w2 = nullptr;\
            return;\
        }\
        else\
        {\
            printf("%s%s %d killed %s%s %d in city %d remaining %d elements\n",RED_BLUE( w1->get_rb() ) ,warriors[w1->get_type()],w1->get_id(),RED_BLUE( w2->get_rb() ), warriors[w2->get_type()],w2->get_id(),_id,w1->get_elements());\
            int n1 = w1->_weaponA.size();\
            deque<weapon> *weapon_tmp =  w2->weapon_out(10 - n1);\
            if(weapon_tmp)\
            {\
                for(size_t i=0;i<weapon_tmp->size();++i)\
                w1->get_weapon( (*weapon_tmp)[i]);\
                delete weapon_tmp;\
            }\
            \
            delete w2;\
            w2 = nullptr;\
            DRAGON_YELL(w1);\
            return;\
        }\
    }\
}

#define BOTH_ALIVE \
    if( !warrior1->is_changed && !warrior2->is_changed)\
{\
    print_time();\
    printf("both red %s %d and blue %s %d were alive in city %d\n",warriors[warrior1->get_type()],warrior1->get_id(), warriors[warrior2->get_type()],warrior2->get_id(),_id);\
    DRAGON_YELL(warrior1);\
    DRAGON_YELL(warrior2);\
    return ;\
}























}


