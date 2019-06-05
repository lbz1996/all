/*
https://leetcode-cn.com/problems/lru-cache/
*/
//最近最少使用?,,,
#include <iostream>
#include <map>
#include <list>
using namespace std;

class LRUCache 
{
public:
    LRUCache(int capacity):_capacity(capacity) {}

    int get(int key) 
    {
       if(m0.count(key)) 
       {
           _priority.remove(key);
           _priority.push_back(key);
           return m0[key].value;
       }
       return -1;
    }

    void put(int key, int value) 
    {
        if(m0.count(key))
        {
            _priority.remove(key);
            _priority.push_back(key);
            m0[key].value = value;
        }
        else
        {
            CacheNode n0(key,value);
            pair<int ,CacheNode> c0(key,n0);
            if( m0.size() == _capacity)
            {
                m0.erase( m0.find( *_priority.begin() ) );//front()?...
                _priority.pop_front();
            }
            _priority.push_back(key);
            m0.insert(c0);
        }
    }

private:

    struct CacheNode 
    {
        CacheNode(){}//......
        CacheNode(int k, int v ):key(k),value(v){}//给默认参数.....
        int key;
        int value;
    };
    map<int,CacheNode> m0;
    list<int> _priority;
    const size_t _capacity;
};









