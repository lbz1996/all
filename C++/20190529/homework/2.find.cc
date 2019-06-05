#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

class TextQuery
{
public:
    int readFile(const string filename);
    void query(const string & word);
private:
    map<string, set<int> > _word2Line;
    vector<string> _lines;
};

int TextQuery::readFile(const string filename)
{
    ifstream fin(filename);
    if( !fin.is_open() )
        return -1;
    string str;
    while(getline(fin,str))
        _lines.push_back(str);
    cout<<"加载完成,行数:"<<_lines.size()<<endl;
    return 0;
}

void TextQuery::query(const string & word)
{
    int count = 0;
    stringstream line;
    string str;
    pair< string,set<int> > p0;
    for(size_t i=0 ;i!=_lines.size() ;++i)
    {
        line << _lines[i];      
        while( line >> str)
        {
            if(str == word)
            {
                if(_word2Line.count(word))
                {
                    ++count;
                    _word2Line[word].insert(i);
                }
                else
                {
                    p0.first = word;
                   _word2Line.insert(p0); 
                }
            }
        }
        line.clear();//清空....
    }

    cout<<word<<" occurs "<<count<<" times."<<endl;
    for(auto it : _word2Line[word])
        cout << "(line " << it << ") "<< _lines[it] << endl;// getline会把换行吞掉...
}


int main(int argc, char *argv[])
{
    TextQuery tq;
    if(2 != argc || -1 ==  tq.readFile(argv[1]) )
    {
        cout<<"wrong input"<<endl;
        return 0;
    }
    string str;
    while(cin >> str)
    {
        cout<<"input word to find"<<endl;
        tq.query(str);            
    }
    return 0;

}       
