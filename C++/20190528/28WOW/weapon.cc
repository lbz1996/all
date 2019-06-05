#include "head.h"
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
    int show_type(){return _type;}
    int show_use(){return _use_time;}
    void set_use(int kase) {_type = kase;}
private:
    int _use_time;
    int _type;
};


