#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
namespace wd
{

class InvertedIndex
{
public:
    InvertedIndex() {}
    ~InvertedIndex() {}
    void readWord()
    {

    }
private:
    unordered_map<string , vector< pair<int,double> > > _invertedIndexTable;
};


}
