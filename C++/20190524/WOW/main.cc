#include "head.h"

int main()
{
    cin>>M>>N>>K>>T;

    for(int i=0;i<5;++i)
        cin>>H[i];
    for(int i=0;i<5;++i)
        cin>>A[i];

    path path0(N);
    //path0.show();

    while(time_now_min<=T)
    {
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

