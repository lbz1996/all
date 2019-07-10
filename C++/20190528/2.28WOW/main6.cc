#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <deque>
using namespace std;

//dragon、ninja、iceman、lion、wolf
#define RED_BLUE(rb) (rb==0?"red ":"blue ")
char warriors[5][20]={"dragon","ninja","iceman","lion","wolf"};
char weapons[3][20]={"sword","bomb","arrow"};

//000:00 blue dragon 1 born
#define PRI_BORN()\
{\
    print_time();\
    cout<<RED_BLUE(_rb)<< warriors[type] << " " << _warrior_id << " born" << endl;\
}\

#define PRI_GO(str,mode)\
{\
    print_time();\
    cout << RED_BLUE( warrior0->get_rb() ) \
    << warriors[warrior0->get_type()] << " " \
    << warrior0->get_id() << str;\
    if(mode)\
    cout<< _pcityArray[i]->show_id();\
    cout << " with " \
    << warrior0->get_elements() << " elements and force " \
    << warrior0->get_atk() << endl;\
}\
//003:10 blue headquarter was taken
#define PRI_TAKON(str)\
{\
    print_time();\
    cout<< str << " headquarter was taken" << endl;\
}\

int M,N,K,T;
int time_now_min= 0;
int H[5];
int A[5];
inline void print_time() { printf("%03d:%02d ",time_now_min/60,time_now_min%60); }

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
    void set_use(int kase) { _use_time = kase; }
private:
    int _use_time;
    int _type;
};

//sword除外
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
    int sort_weapon();
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

class city
{
public:
    city(int id):_id(id) ,warrior1(nullptr) ,warrior2(nullptr),_new_in_1(0),_new_in_2(0){ }//cout<<"city()"<<endl;} 
    city():_id(-1) ,warrior1(nullptr) ,warrior2(nullptr){ }//cout<<"city()"<<endl;} 

    ~city(){ }//cout<<"~city()"<<endl; }

void show()//{cout<<"city: id = "<< _id << " ,warrior1 ->" << warrior1 << " ,warrior2 -> " << warrior2 << endl; }
{printf("city: id=%d, warrior1 -> %16p,warrior2 -> %16p\n",_id,warrior1,warrior2);}
warrior *show_warrior1(){return warrior1;}
warrior *show_warrior2(){return warrior2;}
int show_id(){return _id;}
void set_id(int id){ _id = id; }

void in_warrior(warrior *warrior0,int flag);
bool have_warrior(bool rb){ return rb?warrior2:warrior1; }
void show_warrior_weapon() { if(nullptr!=warrior1) warrior1->show_weapon(); if(nullptr!=warrior2) warrior2->show_weapon(); }
int warrior1_can_go(){return warrior1->get_can_go();}
void set_warrior1_can_go(bool can_go){warrior1->set_can_go(can_go);}
int warrior2_can_go(){return warrior2->get_can_go();}
void set_warrior2_can_go(bool can_go){warrior2->set_can_go(can_go);}
void go(city *left,city *right);
void run()
{
    if(warrior1 && warrior1->get_type() == 3 && ((lion *)warrior1)->get_loyal() <= 0)
    {
        print_time();
        printf("%s%s %d ran away\n",RED_BLUE( warrior1->get_rb() ),warriors[warrior1->get_type()],warrior1->get_id());
        delete warrior1;
        warrior1 = nullptr;
    }

    if(warrior2 && warrior2->get_type() == 3 && ((lion *)warrior2)->get_loyal() <= 0)
    {
        print_time();
        printf("%s%s %d ran away\n",RED_BLUE( warrior2->get_rb() ),warriors[warrior2->get_type()],warrior2->get_id());
        delete warrior2;
        warrior2 = nullptr;
    }
}
void rob()
{//000:35 blue wolf 2 took 3 bomb from red dragon 2 in city 4
    if(warrior1 && warrior2 && warrior1->get_type() == 4 &&warrior2->get_type() != 4) 
    {
        int n1 = warrior1->_weaponA.size();
        deque<weapon> *weapon_tmp = warrior2->weapon_out(10 - n1);
        if(weapon_tmp)
        {
            for(size_t i=0;i<weapon_tmp->size();++i)
                warrior1->get_weapon( (*weapon_tmp)[i]);
            print_time();
            printf("%s %s %d took %ld %s from %s %s %d in city %d\n","red",warriors[warrior1->get_type()],warrior1->get_id(),
                   weapon_tmp->size(),weapons[weapon_tmp->front().show_type()],
                   "blue",warriors[warrior2->get_type()],warrior2->get_id(),_id);
            delete weapon_tmp;
        }
    }
    else if(warrior1 && warrior2 && warrior2->get_type() == 4 &&warrior1->get_type() != 4) 
    {
        int n2 = warrior2->_weaponA.size();
        deque<weapon> *weapon_tmp = warrior1->weapon_out(10 - n2);
        if(weapon_tmp)
        {
            for(size_t i=0;i<weapon_tmp->size();++i)
                warrior2->get_weapon( (*weapon_tmp)[i]);
            print_time();
            printf("%s %s %d took %ld %s from %s %s %d in %d\n","blue",warriors[warrior2->get_type()],warrior2->get_id(),
                   weapon_tmp->size(),weapons[weapon_tmp->front().show_type()],
                   "red",warriors[warrior1->get_type()],warrior1->get_id(),_id);
            delete weapon_tmp;
        }
    }
}

void fight()
{
    //先判断人齐不齐
    if(warrior1 && warrior2)
    {
        //cout<<"fight in :";
        //show();
        int num1 = warrior1->sort_weapon();
        int num2 = warrior2->sort_weapon();
        if(!num1 && !num2)//都没武器算平局
        {//000:40 both red iceman 1 and blue lion 12 were alive in city 2
            //print_time();   
            //printf("both red %s %d and blue %s %d alive in city %d\n",warriors[warrior1->get_type()],warrior1->get_id(),
            //       warriors[warrior2->get_type()],warrior2->get_id(),_id);
            BOTH_ALIVE;
            return;
        }
        //接下来必有一方有武器
        if(_id%2)//奇数方红先攻
        {//000:40 red iceman 1 killed blue lion 12 in city 2 remaining 20 elements
            while(1)
            {
                warrior1->is_changed = 0;
                warrior2->is_changed = 0;
                FIGHT_INSIDE1(warrior1,warrior2);
                FIGHT_INSIDE1(warrior2,warrior1);
                BOTH_ALIVE;
                //printf("in\n1");
            }
        }
        else
        {//000:40 red iceman 1 killed blue lion 12 in city 2 remaining 20 elements
            while(1)
            {
                warrior1->is_changed = 0;
                warrior2->is_changed = 0;
                FIGHT_INSIDE1(warrior2,warrior1);
                FIGHT_INSIDE1(warrior1,warrior2);
                BOTH_ALIVE;
                //printf("in\n");
                //printf("%d %d\n",warrior1->get_elements(),warrior2->get_elements());
            }
        }
    }
}


private:
int _id;
warrior *warrior1;
warrior *warrior2;
bool _new_in_1;
bool _new_in_2;
};

void city::in_warrior(warrior *warrior0,int can_go) 
{ 
    //先走再生产不存在覆盖?.....
    //问号表达式是值,不能作为赋值目标?...
    //!warrior0->get_rb()?warrior1:warrior2 = warrior0;
    warrior0->set_can_go(can_go);
    if(0 == warrior0->get_rb()) 
    {
        warrior1 = warrior0; 
    }
    else
    {
        warrior2 = warrior0; 
    } 
}
void city::go(city *left,city *right)
{
    if( (nullptr != warrior1) && warrior1->get_can_go() && (nullptr != right) )
    {
        if(warrior1->get_type()==3)
            ((lion*) warrior1)->loyal__();
        if(warrior1->get_type()==2)//是最大生命值还是当前生命值啊?....
        {
            ((iceman*) warrior1)->elements__();
            if(warrior1->get_elements()<=0)//假设是当前生命值,所以不会死
            {
                delete warrior1;//(iceman*)???
                warrior1 = nullptr;
                goto label235;
            }
        }
        right->in_warrior(warrior1,0);
        warrior1 = nullptr;
    }
label235:
    if( (nullptr != warrior2) && warrior2->get_can_go() && (nullptr != left) )
    {
        if(warrior2->get_type()==3)
            ((lion*) warrior2)->loyal__();
        if(warrior2->get_type()==2)
        {
            ((iceman*) warrior2)->elements__();
            if(warrior2->get_elements()<=0)
            {
                delete warrior2;//(iceman*)???
                warrior2 = nullptr;
                goto label254;
            }
        }
        left->in_warrior(warrior2,0);
        warrior2 = nullptr;
    }
label254://label后面不能啥也没有....
    return;
}





class home :public city
{
public:
    home(int id ):city(id),_left_elements(M),_warrior_id(1),_rb(id),_is_run(1){ }//cout<<"home()"<<endl; }
    ~home() {  }//cout<<"~home()"<<endl;}
    void home_hp_out() { print_time(); cout <<_left_elements << " elements in " << RED_BLUE(_rb) << "headquarter" << endl; }
    void born(int times);
    private:
    int _left_elements;
    int _warrior_id;//数据成员定义时不能进行初始化
    bool _rb;
    bool _is_run;
};

void home::born(int times)
{
    //dragon、ninja、iceman、lion、wolf
    //iceman、lion、wolf、ninja、dragon 
    //lion、dragon、ninja、iceman、wolf
    //if(_is_run)
    //{
    //先确定生产类型
    int type;
    switch (times)
    {
    case 0:
        type = _rb==0? 2:3;
        break;
    case 1:
        type = _rb==0? 3:0;
        break;
    case 2:
        type = _rb==0? 4:1;
        break;
    case 3: 
        type = _rb==0? 1:2;
        break;
    case 4:
        type = _rb==0? 0:4;
        break;
    }
    //再确定能否生产(不能生产就僵住)
    if(_left_elements < H[type])
    {
        _is_run = 0;
        return;
    }
    else if(_is_run)
    {
        _left_elements -= H[type];
        //dragon、ninja、iceman、lion、wolf
        warrior *warrior0;
        switch (type)
        {
        case 0: 
            warrior0 =new dragon(_rb,_warrior_id,type,H[type],A[type]); 
            in_warrior(warrior0,1);
            warrior0->get_weapon(_warrior_id%3);   
            break;
        case 1: 
            warrior0 =new ninja(_rb,_warrior_id,type,H[type],A[type]); 
            in_warrior(warrior0,1);
            warrior0->get_weapon(_warrior_id%3);   
            warrior0->get_weapon((_warrior_id+1)%3);   
            break;
        case 2: 
            warrior0 =new iceman(_rb,_warrior_id,type,H[type],A[type]); 
            in_warrior(warrior0,1);
            warrior0->get_weapon(_warrior_id%3);   
            break;
        case 3: 
            warrior0 =new lion(_rb,_warrior_id,type,H[type],A[type],_left_elements); 
            in_warrior(warrior0,1);
            warrior0->get_weapon(_warrior_id%3);   
            break;
        case 4: 
            warrior0 =new wolf(_rb,_warrior_id,type,H[type],A[type]); 
            in_warrior(warrior0,1);
            break;
        }
        PRI_BORN();
        if(type == 3)
            printf("Its loyalty is %d\n",_left_elements); 
        ++_warrior_id;
    }
}

class path
{
public:
    path(int N):homeR(0),homeB(N+1),_pcityArray(new city*[N+2])
    {
        //cout<<"path()"<<endl;
        _pcityArray[0]=&homeR;
        _pcityArray[N+1]=&homeB;
        for(int i=1;i<N+1;++i)
            _pcityArray[i] = new city(i);
    }
    ~path()
    {
        //cout<<"~path()"<<endl;
        for(int i=1;i<N+1;++i)
            delete _pcityArray[i];
        delete []_pcityArray;
    }
    void show()
    {
        for(int i=0;i<N+2;++i)
            _pcityArray[i]->show();
    }
    void home_hp_out()
    {
        homeR.home_hp_out();
        homeB.home_hp_out();
    }
    void born(int times)
    {
        homeR.born(times);
        homeB.born(times);
    }
    int go()
    {
        //cout<<"38path go"<<endl;
        int ret = 0;
        for(int i=0;i<N+2;++i)
        {
            if(_pcityArray[i]->show_warrior1())
                _pcityArray[i]->set_warrior1_can_go(1);
            if(_pcityArray[i]->show_warrior2())
                _pcityArray[i]->set_warrior2_can_go(1);
        }
        for(int i=N+1;i>0;--i)
            _pcityArray[i-1]->go(nullptr,_pcityArray[i]);
        for(int i=0;i<N+1;++i)//一共有N+2座城市
            _pcityArray[i+1]->go(_pcityArray[i],nullptr);
        warrior *warrior0;
        for(int i=0;i<N+2;++i)
        {
            if(0 == i)
            {
                if(_pcityArray[i]->show_warrior2())
                {
                    warrior0 = _pcityArray[i]->show_warrior2();
                    PRI_GO(" reached red headquarter",0);
                    ret = 1;
                    PRI_TAKON("red");
                }
            }
            else if(N+1 == i)
            {
                if(_pcityArray[i]->show_warrior1())
                {
                    warrior0 = _pcityArray[i]->show_warrior1();
                    PRI_GO(" reached blue headquarter",0);
                    ret = 1;
                    PRI_TAKON("blue");
                }
            }
            else
            {
                if(_pcityArray[i]->show_warrior1())
                    if(!_pcityArray[i]->warrior1_can_go())
                    {
                        warrior0 = _pcityArray[i]->show_warrior1();
                        PRI_GO(" marched to city ",1);
                    }
                if(_pcityArray[i]->show_warrior2())
                    if(!_pcityArray[i]->warrior2_can_go())
                    {
                        warrior0 = _pcityArray[i]->show_warrior2();
                        PRI_GO(" marched to city ",1);
                    }

            }
        }
        return ret;
    }
    void warriors_weapons_out()
    {
        for(int i=0;i<N+2;++i)
        {
            _pcityArray[i]->show_warrior_weapon();
        }
    }
    void run()
    {
        for(int i=0;i<N+2;++i)
            _pcityArray[i]->run();
    }
    void rob()
    {
        for(int i=0;i<N+2;++i)
            _pcityArray[i]->rob();

    }
    void fight()
    {
        for(int i=0;i<N+2;++i)
            _pcityArray[i]->fight();
    }
private:
    home homeR;
    home homeB;
    city** _pcityArray;
};





int func1()
{

    cin>>M>>N>>K>>T;

    for(int i=0;i<5;++i)
        cin>>H[i];
    for(int i=0;i<5;++i)
        cin>>A[i];

    path path0(N);
    int ret;
    while(time_now_min<=T)
    {
        ret=0;
        switch(time_now_min%60)
        {
        case 0: //生产一个新战士
            path0.born((time_now_min/60)%5);
            break;
        case 5: //lion逃跑
            path0.run();
            break;
        case 10: //前进
            if(path0.go())
                return 0;
            break;
        case 35: //wolf_rob
            path0.rob();
            break;
        case 40: //发生战斗
            path0.fight();
            break;
        case 50: //老家报告生命情况
            path0.home_hp_out();
            break;
        case 55: //战士报告武器情况
            path0.warriors_weapons_out();
            break;
        }
        time_now_min += 5; 
    }
    return 0;
}




int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;++i)
    {
        cout<<"Case "<<i+1<<":"<<endl;
        func1();
    }
    return 0;
}

