#pragma once
#define WORD_MAX_SIZE 1024
#define RET_WORD_NUM 3
#include "Dic.h"
#include "Word.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <errno.h>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
namespace wd
{

class Index_table
{
public:
    Index_table(const string & path)
    {
        _IdxFile = fopen(path.c_str(),"w+");
        if( NULL == _IdxFile )
            perror("wrong Index_table path!");
    }
    ~Index_table() { if(NULL != _IdxFile) fclose(_IdxFile); }
    void cut(const string &str,vector<string> *result)
    {
        result->clear();
        for(auto it:str)
            result->push_back(string{it}); 
    }
    void Build(Dic & dic)
    {//根据词典创建索引表
        //cout<<"idx build in"<<endl;
        vector<string> result;
        pair<string,set<int>> p0;
        int num = dic.GetWordNum();
        //cout << num << "****************" << endl;
        //cout<<"wordNum is "<<num<<endl;
        for(int i=0;i!=num;++i)
        {
            //cout << "Build: " <<dic.GetNStr(i) << endl;
            //cout << "Build: " <<dic.GetNWord(i).GetStr() << endl;
            cut(dic.GetNStr(i),&result);
            //cout << dic.GetNStr(i) << endl;
            for(auto &it:result)
            {
                _idxTable[it].insert(i);
                //if(  _idxTable.count(it))
                //    _idxTable[it].insert(i);
                //else
                //{
                //    p0.first = it;
                //    p0.second.insert(i);
                //    _idxTable.insert(p0);
                //}
            }
        }
        //cout<<"idx build out"<<endl;
    }
    void show() const
    {
        for(auto it:_idxTable)
        {
            cout<<it.first<<" "<<it.second.size()<<endl;
        }
    }
    //void LoadAll() 
    //{
    //    string str;
    //    str.resize(1024);
    //    int frequency;
    //    while( !feof(_IdxFile) )
    //    {
    //        fscanf(_IdxFile,"%s %d",&str[0] ,&frequency);
    //        _dic.push_back(Word(str,frequency));
    //    }
    //}
    //void SaveAll()
    //{
    //    //fseek(_IdxFile,0,SEEK_SET);
    //    rewind(_IdxFile);
    //    for(auto & it:_dic)
    //        fprintf(_IdxFile,"%s %d\n",it.GetStr().c_str(),it.GetFrequency());
    //}
    //void UpdateOne(const string &word)
    //{
    //    for(auto &it : _dic)
    //        if(it.isEqual(word))
    //        {
    //            it.addFrequency();
    //            return;
    //        }
    //    _dic.push_back(Word(word,0)); 
    //    return;
    //}
    vector<Word> MinEditDis(const string str0,Dic * dic)
    {
        //cout << __LINE__ << "in MinEditDis***********************************************************************************" << endl;
        vector<string> MinCut; 
        cut(str0,&MinCut); 
        vector<Word> readyWord;
        pair<int ,int> addedNode;
        addedNode.second = 1;
        unordered_map<int,int> addedWord;
        for(auto &it : MinCut)//先找候选词
        {
            for(auto id : _idxTable[it])
            {
                if( 0 >= addedWord.count(id))
                {
                    addedNode.first = id;
                    addedWord.insert(addedNode);
                    readyWord.push_back(dic->GetNWord(id));
                    //cout << "readyWord: " << dic->GetNStr(id) << endl;
                }
            }
        } 
        int minEditDis = WORD_MAX_SIZE , temp;
        vector<Word> minEditDisWord;
        for(auto &it : readyWord)//再找最短编辑距离的词
        {
            temp = EditDis(str0,it.GetStr());
            if(temp <=  minEditDis)
            {
                if(temp < minEditDis)
                {
                    minEditDis = temp;
                    minEditDisWord.clear();
                    //minEditDisWord.resize(0);

                }
                minEditDisWord.push_back(it);
            }
        }
        //for(auto &it : minEditDisWord)
        //    cout << "minEditDisWord: " << it.GetStr() << " " << it.GetFrequency() << endl; 
        //比较词频
        sort(minEditDisWord.begin(),minEditDisWord.end(),cmp1);
        if(minEditDisWord.size() > RET_WORD_NUM)
            minEditDisWord.resize(RET_WORD_NUM); 
        //cout << __LINE__ << "out MinEditDis" << endl;
        return minEditDisWord;
    }
private:
    int EditDis(const string &str1,const string &str2)
    {
        int dp[WORD_MAX_SIZE][WORD_MAX_SIZE];
        const char *a = str1.c_str();
        const char *b = str2.c_str();
        int len1 = strlen(a+1);
        int len2 = strlen(b+1);
        //初始化
        for(int i=1;i<=len1;i++)
            for(int j=1;j<=len2;j++)
                dp[i][j] = 0x7fffffff;
        for(int i=1;i<=len1;i++)
            dp[i][0] = i;
        for(int j=1;j<=len2;j++)
            dp[0][j] = j;
        for(int i=1;i<=len1;i++)
        {
            for(int j=1;j<=len2;j++)
            {
                int flag;
                if(a[i]==b[j])
                    flag=0;
                else
                    flag=1;
                dp[i][j]=min(dp[i-1][j]+1,min(dp[i][j-1]+1,dp[i-1][j-1]+flag));
                //dp[i-1][j]+1表示删掉字符串a最后一个字符a[i]
                //dp[i][j-1]+1表示给字符串添加b最后一个字符
                //dp[i-1][j-1]+flag表示改变,相同则不需操作次数,不同则需要,用flag记录
            }
        }
        return dp[len1][len2];
    }
    static bool cmp1(const Word &a,const Word &b)
    {
        if( a.GetFrequency() == b.GetFrequency() )
            return a.GetStr() < b.GetStr();
        return a.GetFrequency() > b.GetFrequency();
    }
private:
    unordered_map<string ,set<int> > _idxTable; 
    FILE *_IdxFile;
};


}
