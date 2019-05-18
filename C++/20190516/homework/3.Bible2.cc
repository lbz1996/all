#include <iostream>
#include <iostream>
#include <istream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::ifstream;

typedef struct node
{
    string word;
    int count;
}node;

bool cmp(node a,node b)
{
    return a.count<b.count;
}
class Dictionary
{
public:
    void read(const string &filename);
    void store(const string &filename);
    void print() const;
private:
    map<string,int> _word_count;
    vector<node> _word_count_save;
};

void Dictionary::print() const
{
    for(auto &it:_word_count_save)
        cout<<it.word<<" : "<<it.count<<endl;
}

void Dictionary::read(const string &filename)
{
    ifstream fin(filename);
    string str;
    while(getline(fin,str))
    {
        cout<<str<<endl;
    }
}

void Dictionary::store(const string &filename)
{
    ifstream fin(filename);
    string word;
    while(!fin.eof())
    {
        fin>>word;
        ++_word_count[word];
    }
    node node0;
    for(auto it:_word_count)
    {
        node0.word=it.first;
        node0.count=it.second;
        _word_count_save.push_back(node0);
    }
    sort(_word_count_save.begin(),_word_count_save.end(),cmp);
};


int main()
{
    Dictionary dic1;
    string s0="The_Holy_Bible.txt";
    dic1.store(s0);
    dic1.print();
    //dic1.read(s0);
    return 0;
}

