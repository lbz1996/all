#include "Dic.h"
#include "Index_table.h"
#include <iostream>
using namespace std;
int main(int ,char **argv)
{
    std::cout << "Hello world" << std::endl;
    //argv[0]是自己.........
    cout<<"dic source file is "<<argv[1]<<endl;
    cout<<"dic file save in "<<argv[2]<<endl;
    wd::Dic d0(argv[2]);
    d0.Build(argv[1]);
    d0.LoadAll();
    cout<<"idx file save in "<<argv[3]<<endl;
    wd::Index_table I0(argv[3]);
    I0.Build(d0);
    //I0.show();
    //cout<<"test"<<endl;
    string str;
    vector<wd::Word> result;
    while(cin>>str)
    {
        result = I0.MinEditDis(str,&d0);
        for( auto it:result )
            cout << " " <<it.GetStr()<<" "<<it.GetFrequency()<<endl;
    }
    d0.SaveAll();
    I0.Build(d0);
    I0.show();
    return 0;
}

