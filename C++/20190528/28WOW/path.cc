#include "head.h"

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
        //移动
        //for(int i=0;i<N+2;++i)//一共有N+2座城市
        //{
        //    if(0 == i)
        //        _pcityArray[i]->go(nullptr,_pcityArray[i+1]);
        //    else if(N+1 == i)
        //        _pcityArray[i]->go(_pcityArray[i-1],nullptr);
        //    else
        //        _pcityArray[i]->go(_pcityArray[i-1],_pcityArray[i+1]);
        //}
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
                    //if(!_pcityArray[i]->warrior1_can_go())
                    {
                        warrior0 = _pcityArray[i]->show_warrior2();
                        //001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
                        PRI_GO(" reached red headquarter ");
                        //_pcityArray[i]->set_new_2(0);
                        ret = 1;
                        PRI_TAKON("red");
                    }
                //003:10 blue headquarter was taken
            }
            else if(N+1 == i)
            {
                if(_pcityArray[i]->show_warrior1())
                    //if(!_pcityArray[i]->warrior2_can_go())
                    {
                        warrior0 = _pcityArray[i]->show_warrior1();
                        PRI_GO(" reached blue headquarter ");
                        // _pcityArray[i]->set_new_1(0);
                        ret = 1;
                        PRI_TAKON("blue");
                    }
            }
            else
            {
                //000:10 red iceman 1 marched to city 1 with 20 elements and force 30
                if(_pcityArray[i]->show_warrior1())
                    if(!_pcityArray[i]->warrior1_can_go())
                    {
                        warrior0 = _pcityArray[i]->show_warrior1();
                        PRI_GO(" marched to city ");
                        //_pcityArray[i]->set_new_1(0);
                    }
                if(_pcityArray[i]->show_warrior2())
                    if(!_pcityArray[i]->warrior2_can_go())
                    {
                        warrior0 = _pcityArray[i]->show_warrior2();
                        PRI_GO(" marched to city ");
                        //_pcityArray[i]->set_new_2(0);
                    }

            }
        }
        //cout<<"outpathgo"<<endl;
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
        //cout<<"inpathrun"<<endl;
        for(int i=0;i<N+2;++i)
        {
            _pcityArray[i]->run();
        }
        //cout<<"outpathrun"<<endl;
    }
    void rob()
    {
        //cout<<"inpathrob"<<endl;
        for(int i=0;i<N+2;++i)
        {
           // if(_pcityArray[i]->show_warrior1() && _pcityArray[i]->show_warrior2()
           //    && _pcityArray[i]->show_warrior1()->get_type() == 4 && _pcityArray[i]->show_warrior2()->get_type() != 4)
           //     _pcityArray[i]->rob(0);
           // else if(_pcityArray[i]->show_warrior1() && _pcityArray[i]->show_warrior2()
           //    && _pcityArray[i]->show_warrior1()->get_type() != 4 && _pcityArray[i]->show_warrior2()->get_type() == 4)
                _pcityArray[i]->rob();
            
        }
        //cout<<"inpathrob"<<endl;
    }
    void fight()
    {
        for(int i=0;i<N+2;++i)
        {
            _pcityArray[i]->fight();
        }
    }
private:
    home homeR;
    home homeB;
    city** _pcityArray;
};

