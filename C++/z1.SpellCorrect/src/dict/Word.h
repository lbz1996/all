#pragma once
#include <string>
#include <iostream>
using std::string;
namespace wd
{

class Word
{
public:
    Word() { std::cout << "不加vector。resize 用不了。。。 " << std::endl; }
    Word(const string & word,int frequency):_word(word),_frequency(frequency) {}
    ~Word() {}
    //bool operator == (const Word &a) { return  a._word == _word; }
    //bool operator != (const Word &a) { return  a._word != _word; }
    void addFrequency() { ++_frequency; }
    bool isEqual(const string &word) { return _word == word; }
    string  GetStr() const { return _word; }
    int GetFrequency() const { return _frequency; }
private:
    string _word;
    int _frequency;
};


}
