#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>
using namespace std;
namespace wd
{

class Filter
{
public:
    Filter(const string &path_stopWords = "/home/lbz/github/all/C++/SearchSource/src/cppjieba/dict/stop_words.utf8"):_path_stopWords(path_stopWords)
    {
        ifstream stopWords_in(path_stopWords);
        if(stopWords_in.good())
        {
            string word;
            while(true)
            {
                stopWords_in >> word;
                if(stopWords_in.eof())
                    break;
                else
                {
                   _stopWords.insert(word); 
                }
            }
        }
        else
        {
            cout << "wrong in Filter()" << endl;
        }
        stopWords_in.close();
        //for(auto it:_stopWords)
            //cout << it << endl;
    }
vector<string> Filter_word(const vector<string> &words)
{
    vector<string> out;
    for(const auto &it:words)
    {
        if(it == "\n"||it == "\n\n")
            continue;
        if( 0 == _stopWords.count(it) )
        {
            out.push_back(it);
        }
    }
    return out;
}
private:
    string _path_stopWords;
    set<string> _stopWords;
};

}
