#include <iostream>
#include <cstdlib>
#include <limits.h>
#include "../inc/tinyxml2.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "boost/regex.hpp"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace tinyxml2; 
using std::ofstream;
//using namespace boost;

namespace wd
{

struct RssItem//feed中的一个文章story
{
public:
    RssItem()
    :_title("无标题") {  }
    ~RssItem(){  }
public:
    string _title;//标题
    string _link;//超链接
    string _description;//描述
    string _content;//内容???
    string _contentTitle;
};

class RssReader
{
public:
    RssReader()
    :_path_rssResource("../data/rss源语料")
    ,_path_ripepage("../data/ripepage.lib")
    ,_path_offset("../data/offset.lib") 
    ,_docid(0){ }

    RssReader(string path_rssResource,string path_ripepage,string _path_offset)
    :_path_rssResource(path_rssResource),_path_ripepage(path_ripepage),_path_offset(_path_offset)
    ,_docid(0){ }

    int parseRssAll() //打开目录,对每个xml文件调用parseRss函数
    {
        DIR *dir = opendir(_path_rssResource.c_str());        
        if(NULL == dir) { cout << "rss源语料地址错误,需要正确目录" << endl; return -1; }       
        cout << _path_rssResource << endl;
        char curr_path[1024] = {0};
        getcwd(curr_path,1024);
        chdir(_path_rssResource.c_str());
        struct dirent *file;
        //struct stat statbuf;
        while( (file = readdir(dir)) != NULL) //如果是文件且后缀是.xml就调用parseRss
        {
            //stat(file->d_name,&statbuf); //char ext[32]; //_splitpath( file->d_name, nullptr, nullptr, nullptr, ext ); //linux下没有?..  //if( 0 == strcmp(ext , ".xml") )
            string filename = file->d_name;  
            if( std::string::npos != filename.rfind(".xml"))
            {
                parseRss(file->d_name);
            }
        }
        chdir(curr_path);
        dump(); 
        closedir(dir);
        return 0;
    }

private:
    void dump()
    {
        cout << endl << _path_ripepage << endl;
        cout << _rss.size() << endl;
        ofstream _ripepage(_path_ripepage); 
        ofstream _offset(_path_offset);
        std::ofstream::pos_type offset;
        std::ofstream::pos_type lengthgg;
        for(size_t i = 0;i<_rss.size();++i)
        {
            offset = _ripepage.tellp();
            _ripepage<< "<doc>" << endl
                     << "\t" << " <docid>" << i << "</docid>" <<endl
                     << "\t" << " <title>" << _rss[i]._title << "</title>" << endl
                     << "\t" << " <link>" << _rss[i]._link << "</link>" << endl
                     << "\t" << " <content>" << _rss[i]._content << "</content>" << endl
                     << "</doc>" <<endl;
                     //<<"********************************************************************************************************"<<endl;
            lengthgg = _ripepage.tellp() - offset; 
            _offset  << i << " " << offset << " " << lengthgg << endl;
        }
        _ripepage.close();
        _offset.close();
    }
    void parseRss(const char *filename)
    {
        cout << filename << endl;
        char abs_path0[1024];
        bzero(abs_path0,1024);
        realpath(filename,abs_path0);
        cout << abs_path0 << endl;
        if(0 == sizeof(abs_path0)) { cout << "open error" << endl; return; }

        XMLDocument doc;//声明一个XML文档
        doc.LoadFile(abs_path0);//加载
        if(0 != doc.Error()) { cout<<"load error"<<endl; return; }
          
        XMLElement *root = doc.RootElement();//rss声明???
        XMLElement *channel = root-> FirstChildElement("channel"); //只找3channel元素
        if(NULL==channel) { cout<<"channel error"<<endl; return ; }
        //XMLElement * title = channel->FirstChildElement("title");
        //cout<<title->GetText()<<endl;
        //cout<<title->Name()<<endl;
        XMLElement * item=channel->FirstChildElement("item");
        while(item)
        {
            RssItem tmp;
            memset(&tmp,0,sizeof(RssItem));
            tmp._link = abs_path0;
            //tmp._link = abs_path; 
            XMLElement *item_child = item->FirstChildElement();
            //regex pattern;
            //pattern = "content?:*";
            //smatch matchs;
            //cout << item_child << endl;
            while(item_child)
            {
                string child_name=item_child->Name();
                //cout << item_child->Name() << endl;
                if(child_name == "title")
                {
                    string child_title = item_child->GetText();
                    if(child_title.size())
                        tmp._title = item_child->GetText();
                }
                //要绝对路径,离线?
                //else if(0==strcmp(item_child->Name(),"link"))//link = url ???
                //{
                //    tmp._link = item_child->GetText();
                //}
                else if(0==strcmp(item_child->Name(),"description"))
                {
                    tmp._description = item_child->GetText();
                }
                else if(0==strcmp(item_child->Name(),"content:encoded"))
                //else if(regex_search(child_name,matchs,pattern))
                {
                    tmp._content += item_child->GetText();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }
                item_child = item_child->NextSiblingElement();
            }
            if( 0 == strcmp (tmp._title.c_str() , "无标题" ))
            {
                std::stringstream  stringIO;
                if( 0 != tmp._content.size() )
                {
                    stringIO << tmp._content; //如果无内容?
                    stringIO >> tmp._title;
                }
            }
            _rss.push_back(tmp);
            item = item->NextSiblingElement();
        }
    }
private:
    vector<RssItem> _rss;
    string _path_rssResource;
    string _path_ripepage;
    string _path_offset;
    long _docid;
};


}
int main(int argc,char **argv)
{
    wd::RssReader r1;
    if(4 == argc)
        r1 = wd::RssReader(argv[1],argv[2],argv[3]);
    r1.parseRssAll();
    //r1.parseRss("coolshell.xml");
    //r1.dump("../data/ripepage.lib");
    return 0;
}

