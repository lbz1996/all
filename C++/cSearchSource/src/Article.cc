#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
namespace wd
{

class Article
{
public:
    Article(long docid
            ,const string &path_offset = "/home/lbz/github/all/C++/SearchSource/data/offset.lib"
            //,const string &path_offset = "../data/offset.lib"
            //,const string &path_ripepage = "~/github/all/C++/SearchSource/data/ripepage.lib")//~???
            ,const string &path_ripepage = "/home/lbz/github/all/C++/SearchSource/data/ripepage.lib")//注意现在不是newripepage
    :_docid(docid)
    ,_begin(0)
    ,_length(0)
    ,_article()
    ,_path_offset(path_offset)
    ,_path_ripepage(path_ripepage)
    {
        cout << _docid << endl;
        long id = -1;
        cout << _path_offset << endl;
        ifstream offset_in(_path_offset);
        //cout << offset_in.fail() << endl;
        //cout << offset_in.good() << endl;
        //cout << offset_in.bad() << endl;
        //cout << offset_in.eof() << endl;
        string cline;
        while(!offset_in.eof())
        {
            ++id;
            getline(offset_in,cline);
            if(id != _docid)
                continue;
            else
            {
                stringstream line(cline);
                line >> _docid >> _begin >> _length;
                offset_in.close();

                char *article = (char*) calloc(1,_length);
                FILE *rigepage_in = fopen(_path_ripepage.c_str(),"r");
                if(rigepage_in)
                {
                    fseek(rigepage_in,_begin,0);
                    fread(article,1,_length,rigepage_in);
                    //cout << "begin*************************" << endl;
                    //cout << article << endl;
                    //cout << "close*************************" << endl;
                    _article = article;
                    free(article);
                    fclose(rigepage_in);
                    return;
                }
            }
        }
        offset_in.close();
        cout << "wrong!!!" << endl;
        docid = -1;
    }
    const string &Get_Article() const { return _article; }
private:
    long _docid;
    long _begin;
    long _length;
    string _article;
    string _path_offset;
    string _path_ripepage;
    vector<string> _words;
};

}
//int main()
//{
//    wd::Article a1(0);    
//    wd::Article a2(3);    
//    wd::Article a3(20);    
//}
