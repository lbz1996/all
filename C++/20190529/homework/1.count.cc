#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <unordered_map>
using namespace std;

#define node pair<string,int>
bool cmp(node l,node r) { return l.second < r.second; }

void count1()
{
    clock_t start_time,end_time;
    start_time = clock();

    vector<node> v0;
    ifstream fin("The_Holy_Bible.txt");
    string str;
    node n0;
    int is_find ;
    while(fin>>str)
    {
        is_find = 0;
        for(vector<node>::iterator it = v0.begin();it !=v0.end();++it)
        {
            if(it->first==  str)
            {
                ++it->second; 
                is_find = 1;
                break;
            }
        }
        if(!is_find)
        {
            n0.first= str;
            n0.second= 1;
            v0.push_back(n0);
        }
    }
    sort(v0.begin(),v0.end(),cmp);

    cout<<"total is "<<v0.size()<<endl;
    for(vector<node>::iterator it = v0.end() - 10 ; it != v0.end(); ++it)
        cout<<it->first<<" "<<it->second<<endl;

    end_time = clock();
    cout << "runtime is "<<(double)(end_time - start_time) / CLOCKS_PER_SEC <<"s"<<endl;
}


void count2()
{
    clock_t start_time,end_time;
    start_time = clock();

    map<string,int> m0;//......
    ifstream fin("The_Holy_Bible.txt");
    pair<string,int> pair0;
    while(fin>>pair0.first)
    {
        pair0.second = 1;
        if(m0.count(pair0.first))
            ++m0[pair0.first];//不能直接访问,可能不存在,先判断......
        else
            m0.insert(pair0);
    }
    vector<node> v0;
    for(auto it:m0)
        v0.push_back(it);
    sort(v0.begin(),v0.end(),cmp);

    cout<<"total is "<<v0.size()<<endl;
    for(vector<node>::iterator it = v0.end() - 10 ; it != v0.end(); ++it)
        cout<<it->first<<" "<<it->second<<endl;

    end_time = clock();
    cout << "runtime is "<<(double)(end_time - start_time) / CLOCKS_PER_SEC <<"s"<<endl;
}

void count3()
{
    clock_t start_time,end_time;
    start_time = clock();

    unordered_map<string,int> m0;//......
    ifstream fin("The_Holy_Bible.txt");
    pair<string,int> pair0;
    while(fin>>pair0.first)
    {
        pair0.second = 1;
        if(m0.count(pair0.first))
            ++m0[pair0.first];//不能直接访问,可能不存在,先判断......
        else
            m0.insert(pair0);
    }
    vector<node> v0;
    for(auto it:m0)
        v0.push_back(it);
    sort(v0.begin(),v0.end(),cmp);

    cout<<"total is "<<v0.size()<<endl;
    for(vector<node>::iterator it = v0.end() - 10 ; it != v0.end(); ++it)
        cout<<it->first<<" "<<it->second<<endl;

    end_time = clock();
    cout << "runtime is "<<(double)(end_time - start_time) / CLOCKS_PER_SEC <<"s"<<endl;

}

int main()
{
    std::cout << "Hello world" << std::endl;
    count1();
    count2();
    count3();
    return 0;
}

