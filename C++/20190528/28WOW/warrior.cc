#include "head.h"


#define PUSH_POP() do\
{\
    _weaponA[0].set_use(_weaponA[0].show_use() - 1);\
    if(_weaponA[0].show_use() != 0)\
    _weaponR.push_back(_weaponA[0]);\
    _weaponA.pop_front();\
}while(0)

class warrior
{
public:
    warrior(bool rb,int id,int type,int elements,int atk):_rb(rb),_id(id),_type(type),_elements(elements),_atk(atk),_can_go(1){}
    ~warrior(){}//cout<<"~warrior"<<endl;}

    int get_rb(){return _rb;}
    int get_id(){return _id;}
    int get_type(){return _type;}
    int get_elements(){return _elements;}
    int get_atk() { return _atk; }

    void get_weapon(weapon weapon0) { if(_weaponA.size()<10) _weaponA.push_back(weapon0);   }
    void show_weapon();
    int sort_weapon();
    deque<weapon> *weapon_out(int num);
    int use_weapon();

    int get_harmed(int harmed) { is_changed = harmed; _elements -= harmed; return _elements; }
    void set_elements(int elements){_elements = elements;};//???.....

    int get_can_go(){return _can_go;} 
    void set_can_go(bool can_go){_can_go = can_go;}
public:
    bool is_changed;
    deque<weapon> _weaponA;
    vector<weapon> _weaponR;
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
    printf("%s %s %d has %d sword %d bomb %d arrow and %d elements\n",_rb?"blue":"red",warriors[_type],_id,out[0],out[1],out[2],_elements);
}

int warrior::use_weapon()
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
            PUSH_POP();
            if(_type != 1)
                _elements -= atk * 4/10;
            return atk * 4/10; 
        case 2:
            PUSH_POP();
            return atk * 3/10; 
        }
    }
    return 0;
}




bool cmp1(weapon weapon1,weapon weapon2) { return weapon1.show_type() < weapon2.show_type(); }
bool cmp2(weapon weapon1,weapon weapon2) { return weapon1.show_use() > weapon2.show_use(); }
bool cmp3(weapon weapon1,weapon weapon2) { return weapon1.show_use() < weapon2.show_use(); }
int warrior::sort_weapon()
{
    sort(_weaponA.begin(),_weaponA.end(),cmp1);
    return _weaponA.size();
}
deque<weapon> *warrior::weapon_out(int num)
{
    if(_weaponA.size()!=0)
    {
        deque<weapon> *weapon_tmp = new deque<weapon>;//接收的要负责删除...
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
        {
            weapon_tmp->push_back(_weaponA[i]);
        }

        for(int i=0;i<num2;++i)
        {
            //_weaponA.erase(_weaponA.begin());
            _weaponA.pop_front();
        }
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
    {set_elements(get_elements()*9/10);}//假设为当前
};
class lion:public warrior
{
public:
    lion(bool rb,int id,int type,int elements,int atk,int loyal):warrior(rb,id,type,elements,atk),_loyal(loyal){}
    int get_loyal(){return _loyal;}
    void loyal__()
    {
        //cout<<"loyal__"<<endl;
        _loyal -= K;
    }
private:
    int _loyal;
};
class wolf:public warrior 
{
public:
    wolf(bool rb,int id,int type,int elements,int atk):warrior(rb,id,type,elements,atk){}
};

