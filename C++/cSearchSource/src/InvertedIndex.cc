//#pragma once
#include "CostTime.cc"
#include "Filter.cc"
#include "Offset.cc"
#include "Article.cc"
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "./cppjieba/include/cppjieba/Jieba.hpp"
//#include <unordered_map>
using namespace std;
namespace wd
{
class Word
{
public:
    Word(const string &word):_TF(0),_DF(0),_IDF(0),_w(0),_word(word) {  }
    bool operator =(const Word &hs) { return hs._word == _word; }
    int _TF;//一篇文章......
    int _DF;//所有文章
    int _IDF;//所有文章
    double _w;//权重,一篇文章
    string _word;
};

class InvertedIndex
{
public:
    InvertedIndex(
                  const char* const DICT_PATH = "/home/lbz/github/all/C++/SearchSource/src/cppjieba/dict/jieba.dict.utf8",
                  const char* const HMM_PATH = "/home/lbz/github/all/C++/SearchSource/src/cppjieba/dict/hmm_model.utf8",
                  const char* const USER_DICT_PATH = "/home/lbz/github/all/C++/SearchSource/src/cppjieba/dict/user.dict.utf8",
                  const char* const IDF_PATH = "/home/lbz/github/all/C++/SearchSource/src/cppjieba/dict/idf.utf8",
                  const char* const STOP_WORD_PATH = "/home/lbz/github/all/C++/SearchSource/src/cppjieba/dict/stop_words.utf8",
                  const char* const path_invertedIndex = "/home/lbz/github/all/C++/SearchSource/data/invertIndex.lib"
                 )
        : _jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH)
          ,_path_InvertedIndex(path_invertedIndex) { }

    ~InvertedIndex() {}
    void Build()
    {
        Offset offset0;
        long N = offset0.Get_OffsetLength();
        for(long i=0;i!=N;++i)
        {
            vector<string> words;
            Article article0(i);
            words = ReadWord(article0.Get_Article());
            for(const string &it:words)
            {
                if(1 == _counts.count(it)) 
                {
                    if(1 == _counts[it].count(i))
                        ++_counts[it][i];
                    else
                        _counts[it].insert(pair<long,long>(i,1));//......
                }
                else//......
                {
                    pair<string , unordered_map< long,long > > Node;
                    Node.first = it;
                    pair<long,long> smallNode;
                    smallNode.first = i;
                    smallNode.second = 1;
                    Node.second.insert(smallNode);
                    _counts.insert(Node);
                }
            }
        }
        for(const auto &it1 : _counts)
        {
            //for(const auto &it2 : it1.second)
            //{
            if(0 == _countsDF.count(it1.first))
                _countsDF.insert(pair<string,long>(it1.first,1));
            else
                ++_countsDF[it1.first];
            //}
        }
        for(const auto &it1 : _countsDF)
        {
            _countsIDF.insert(pair<string , double>(it1.first,log(N/(it1.second + 1)) ));
            //cout << log(N/(it1.second + 1)) << endl;
        }
        for(long i=0;i!=N;++i)
        {
            vector<string> words;
            Article article0(i);
            words = ReadWord(article0.Get_Article());
            //double d0 = 0;
            long double d3 = 0;
            for(const string &it:words)  
            {
                //cout << "TF is " << _counts[it][i] << endl;
                //cout << "DF is " << _countsDF[it] << endl;
                //cout << "IDF is " << _countsIDF[it] << endl;
                long double d1 =_counts[it][i] * _countsIDF[it];
                //cout << "d1 is " << d1 << endl;
                //cout << "d1 * d1 is " << d1 * d1 << endl;
                d3 += d1;
                //cout << "d3 is " << d3 << endl;
                //d0 += _counts[it][i] * _counts[it][i] * _countsIDF[it] * _countsIDF[it];
                //cout << "d0 is " << d0 << endl;
            }
            d3 = sqrt(d3);
            //cout << d0 << endl;
            for(const string &it:words)
            {
                double _w = _counts[it][i] * _countsIDF[it] / d3 ;
                //cout << _w << endl;
                if(0 == _invertedIndexTable.count(it))
                {
                    vector<pair<long , double>> v0;
                    v0.push_back(pair<long , double>(i,_w));
                    _invertedIndexTable.insert(pair<string,vector<pair<long,double>>>(it,v0));
                }
                else
                {
                    int flag = 1;
                    for(auto it2 : _invertedIndexTable[it])
                    {
                        if(it2.first == i)
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if(flag)
                        _invertedIndexTable[it].push_back(pair<long,double>(i,_w));
                }
            }
        }
        ofstream InvertedIndex_in(_path_InvertedIndex);
        for(auto it1:_invertedIndexTable)
        {
            InvertedIndex_in << it1.first;
            for(auto it2 : it1.second)
            {
                InvertedIndex_in << " " << it2.first << " " << it2.second;
            }
            InvertedIndex_in << endl;
        }
        InvertedIndex_in.close();
    }
    void Read()
    {
        wd::CostTime CS0("Read");
        ifstream InvertedIndex_in(_path_InvertedIndex);
        typedef pair<string,vector<pair<long ,double>>>  bigNode;
        typedef pair<long,double> smallNode;
        bigNode b0;
        string line;
        while(getline(InvertedIndex_in , line) && !InvertedIndex_in.eof())
        {
            stringstream sline(line);
            sline >> b0.first; 
            //cout << b0.first;
            long l;
            double d;
            while( sline >> l >> d )
            {
                b0.second.push_back(smallNode(l,d));
                //cout << " " << l << " " << d;
                if(sline.eof())
                    break;
            }
            //cout << endl;
            _invertedIndexTable.insert(b0);
        }
        InvertedIndex_in.close();
        CS0.end();
    }
    void simple()//去重
    {
    }
private:
    vector<string> ReadWord(const string &article)
    {
        wd::CostTime CS0("ReadWord");
        vector<string> words;
        //jieba.Cut(article, words, true);
        _jieba.CutForSearch(article,words,true);
        words = _f0.Filter_word(words);
        //cout << "***************************" << endl;
        //for(unsigned long i = 0 ;i!=words.size();++i)
        //    cout << words[i] << endl;
        //cout << "***************************" << endl;
        return words;
        CS0.end();
    }
private:
    cppjieba::Jieba _jieba;//初始化会花好长时间
    Filter _f0;
    string _path_InvertedIndex;
    //unordered_map<string ,vector<pair<long ,long >> > _counts;
    unordered_map<string ,unordered_map<long ,long > > _counts;//TF
    unordered_map<string , long > _countsDF;//DF
    unordered_map<string , double > _countsIDF;//IDF
    //unordered_map<string , double > _countsW;//w
    unordered_map<string , vector< pair<long,double> > > _invertedIndexTable;
};

}

int main()
{
    wd::CostTime CS0("main");
    wd::InvertedIndex I0;
    I0.Build();
    //I0.Read();
    CS0.end();
    return 0;
}
