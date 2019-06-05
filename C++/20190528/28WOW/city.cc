#include "head.h"

#define FIGHT_INSIDE1(w1,w2) \
    if(w1->_weaponA.size()!=0)\
{\
    w2->get_harmed(w1->use_weapon());\
    if(w2->get_elements()<0)\
    {\
        if(w1->get_elements()<0)\
        {\
            print_time();\
            printf("both red %s %d and blue %s %d died in city %d\n",warriors[w1->get_type()],w1->get_id(), warriors[w2->get_type()],w2->get_id(),_id);\
            return;\
        }\
        print_time();\
        if(w1->get_rb())\
            printf("red %s %d killed blue %s %d int city %d remaining %d elements\n", warriors[w2->get_type()],w2->get_id(),warriors[w1->get_type()],w1->get_id(),_id,w1->get_elements());\
        else\
            printf("red %s %d killed blue %s %d int city %d remaining %d elements\n", warriors[w1->get_type()],w1->get_id(),warriors[w2->get_type()],w2->get_id(),_id,w1->get_elements());\
        \
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
        if(0 == w1->get_type())\
        {\
            print_time();\
            printf("%s %s %d yelled in city %d\n",w1->get_rb()?"blue":"red",warriors[w1->get_type()],w1->get_id(),_id);\
        }\
        return;\
    }\
}

#define BOTH_ALIVE \
    if( !warrior1->is_changed && !warrior2->is_changed)\
{\
    print_time();\
    printf("both red %s %d and blue %s %d alive in city %d\n",warriors[warrior1->get_type()],warrior1->get_id(), warriors[warrior2->get_type()],warrior2->get_id(),_id);\
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
bool show_new_1(){return _new_in_1;}
bool show_new_2(){return _new_in_2;}
void set_new_1(int new1){_new_in_1 = new1;}
void set_new_2(int new2){_new_in_2 = new2;}
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
    //cout<<"incityrun"<<endl;
    if(warrior1 && warrior1->get_type() == 3 && ((lion *)warrior1)->get_loyal() <= 0)
    {
        print_time();
        printf("%s %s %d run\n",warrior1->get_rb()?"bule":"red",warriors[warrior1->get_type()],warrior1->get_id());
        delete warrior1;
        warrior1 = nullptr;
    }

    if(warrior2 && warrior2->get_type() == 3 && ((lion *)warrior2)->get_loyal() <= 0)
    {
        print_time();
        printf("%s %s %d run\n",warrior2->get_rb()?"bule":"red",warriors[warrior2->get_type()],warrior2->get_id());
        delete warrior2;
        warrior2 = nullptr;
    }
    //cout<<"outcityrun"<<endl;
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
            printf("%s %s %d took %ld %s from %s %s %d in %d\n","red",warriors[warrior1->get_type()],warrior1->get_id(),
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
            if(warrior1->get_elements()<=0)
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
    void home_hp_out() { print_time(); cout <<_left_elements << " elements in " << RED_BLUE << "headquarter" << endl; }
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


