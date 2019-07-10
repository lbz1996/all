#pragma once
#include "Word.h"
#include <cstdio>
#include <iostream>
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
//using std::vector;
//using std::cout;
//using std::endl;
//using std::FILE;
namespace wd
{

class Dic
{
public:
    Dic(string  path):_dicFilePath(path) { }
    ~Dic() {};
    //Dic(const string & path)
    //{
    //    _dicFile = fopen(path.c_str(),"w+");
    //    if( NULL == _dicFile )
    //        perror("wrong dic path!");
    //}
    //~Dic() { if(NULL != _dicFile) fclose(_dicFile); }

    string GetNStr(int n) { return _dic[n].GetStr(); }
    Word GetNWord(int n){return _dic[n];}
    int GetWordNum() { return _dic.size(); }

    void Build(const string & source)
    {
        //cout << _dicFilePath << endl;
        _dicFile = fopen(_dicFilePath.c_str(),"w+");
        if( NULL == _dicFile )
        {
            cout<< __LINE__ <<endl;
            perror("wrong dic path!");
        }
        clock_t start_time,end_time;
        start_time = clock();

        unordered_map<string,int> m0;//......
        ifstream fin(source.c_str());
        pair<string,int> pair0;
        //string str;
        while(fin>>pair0.first)
        {
            //cout << pair0.first << endl;
            pair0.second = 1;
            if(m0.count(pair0.first))
                ++m0[pair0.first];//不能直接访问,可能不存在,先判断......
            else
                m0.insert(pair0);
        }
        //vector<Word> v0;
        //for(auto &it:m0)
        //    v0.push_back(Word(it.first,it.second));
        //sort(v0.begin(),v0.end(),cmp);//词典不用排序吧...
        //cout<<"total is "<<v0.size()<<endl;
        for(auto &it:m0)
            fprintf(_dicFile,"%s %d\n",it.first.c_str(),it.second);
        cout<<"total is "<<m0.size()<<endl;
        end_time = clock();
        cout << "runtime is "<<(double)(end_time - start_time) / CLOCKS_PER_SEC <<"s"<<endl;
        fin.close();
        fclose(_dicFile);
    }
    void LoadAll() 
    {
        ifstream fin(_dicFilePath);
        string str;
        int seq;
        while(fin >> str >> seq)
        {
            _dic.push_back(Word(str,seq));
        }
        fin.close();
        //_dicFile = fopen(_dicFilePath.c_str(),"r+");
        //if( NULL == _dicFile )
        //    perror("wrong dic path!");
        //string str;
        //str.resize(1024);
        //int frequency;
        //fseek(_dicFile,0,SEEK_SET);
        ////rewind(_dicFile);
        ////????有啥区别
        //while( !feof(_dicFile) )
        //{
        //    fscanf(_dicFile,"%s %d",&str[0] ,&frequency);
        //    _dic.push_back(Word(str,frequency));
        //}
        //fclose(_dicFile);
    }
    void SaveAll()
    {
        _dicFile = fopen(_dicFilePath.c_str(),"w+");
        if( NULL == _dicFile )
            perror("wrong dic path!");
        fseek(_dicFile,0,SEEK_SET);
        //rewind(_dicFile);
        for(auto & it:_dic)
            fprintf(_dicFile,"%s %d\n",it.GetStr().c_str(),it.GetFrequency());
        fclose(_dicFile);
    }
    void UpdateOne(const string &word)
    {
        for(auto &it : _dic)
            if(it.isEqual(word))
            {
                it.addFrequency();
                return;
            }
        _dic.push_back(Word(word,0)); 
        return;
    }
private:
    vector<Word> _dic;
    FILE *_dicFile;
    string _dicFilePath;
};


}
