#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Solution 
{
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
    {
        int minkase = 0;
        vector<bool> can_use(wordList.size(),true);
        find1(beginWord,endWord,wordList,can_use,1,&minkase);
        return minkase;
    }

    void find1(string &beginWord,string &endWord,vector<string> &wordList,vector<bool> can_use,int used,int *minkase)//递归...
    {
        int length = wordList.size();
        
        for(int i=0;i<length;++i)
        {
            if(wordList[i] == beginWord)
            {
                can_use[i] = false;
                break;
            }
        }

        for(int i=0;i<length;++i)
        { 
            if(can_use[i] == true && can_next(beginWord,wordList[i]))
            {
                if(wordList[i] == endWord)
                {
                    *minkase = used + 1;
                    return;
                }
                else
                {
                    find1(wordList[i],endWord,wordList,can_use,used+1,minkase);
                }
            }
        }
        return;
    }

    bool can_next(string &begin,string &another)
    {
        size_t length = begin.size();
        size_t not_equal=0;
        for(size_t i=0;i<length;++i)
        {
            if(begin[i]!=another[i])
                ++not_equal;
            if(not_equal>1)
                return false;
        }
        return true;
    }
};

