#include <iostream>
#include "tinyxml2.h"
#include <string>
#include <vector>
#include <fstream>
#include "boost/regex.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace tinyxml2; 
using std::ofstream;
using namespace boost;

struct RssItem//feed中的一个文章story
{
public:
    ~RssItem(){cout<<"析构函数"<<endl;}
public:
    string title;//标题
    string link;//超链接
    string description;//描述
    string content;//内容???
};

class RssReader
{
public:
    //RssReader();
    void parseRss(const char *filename)
    {
        //cout<<"input a XMLDocument"<<endl;
        //string name; cin>>name;
        XMLDocument doc;//声明一个XML文档
        //doc.LoadFile(name.c_str());//加载
        doc.LoadFile(filename);//加载
        if(0!=doc.Error()) { cout<<"load error"<<endl; return; }
        XMLElement *root = doc.RootElement();//rss声明???

        XMLElement *channel = root-> FirstChildElement("channel"); //只找3channel元素
        if(NULL==channel) { cout<<"channel error"<<endl; return ; }
        XMLElement * title = channel->FirstChildElement("title");
        cout<<title->GetText()<<endl;
        cout<<title->Name()<<endl;
        XMLElement * item=channel->FirstChildElement("item");
        while(item)
        {
            cout<<"sucess in item"<<endl;
            RssItem tmp;
            XMLElement *item_child = item->FirstChildElement();
            regex pattern;
            pattern = "content?:*";
            smatch matchs;
            while(item_child)
            {
                string child_name=item_child->Name();
                if(0==strcmp(item_child->Name(),"title"))
                {
                    tmp.title = item_child->GetText();
                }
                else if(0==strcmp(item_child->Name(),"link"))
                {
                    tmp.link = item_child->GetText();
                }
                else if(0==strcmp(item_child->Name(),"description"))
                {
                    tmp.description = item_child->GetText();
                }
                //else if(0==strcmp(item_child->Name(),"content:encoded"))
                else if(regex_search(child_name,matchs,pattern))
                {
                  tmp.content += item_child->GetText();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }
                item_child = item_child->NextSiblingElement();
            }
            _rss.push_back(tmp);
            item = item->NextSiblingElement();
        }
    }
    void dump(const string & filename)
    {
        ofstream file_out(filename); 
        for(size_t i = 0;i<_rss.size();++i)
        {
            file_out<<"<doc>"<<endl
                <<" <docid>"<<i<<"</docid>"<<endl
                <<" <title>"<<_rss[i].title<<"</title>"<<endl
                <<" <link>"<<_rss[i].link<<"</link>"<<endl
                <<" <content>"<<_rss[i].content<<"</content>"<<endl
                <<"</doc>"<<endl
                <<"********************************************************************************************************"<<endl;
        }
    }
private:
    vector<RssItem> _rss;
};
int main()
{
    RssReader r1;
    r1.parseRss("coolshell.xml");
    r1.dump("pagelib.txt");
    return 0;
}

