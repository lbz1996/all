#include <iostream>
#include <iostream>
#include <istream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::ifstream;


class Dictionary
{
public:
    void read(const string &filename);
    void store(const string &filename);
    void print() const;
private:
    vector<string> _words;
    vector<int> _counts;
};

void Dictionary::print() const
{
    for(size_t i=0;i!=_words.size();++i)
        cout<<_words[i]<<" : "<<_counts[i]<<endl;
    cout<<_words.size()<<endl;
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
    int flag;
    while(!fin.eof())
    {
        flag=0;
        fin>>word;
        for(size_t i=0;i!=_words.size();++i)
        {
            if(_words[i]==word)
            {
                flag=1;
                _counts[i]++;
                break;
            }
        }
        if(0==flag)
        {
            _words.push_back(word);
            _counts.push_back(1);
        }
    }
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

