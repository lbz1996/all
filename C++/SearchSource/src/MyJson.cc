#include <iostream>
#include <vector>
#include <string>
#include <json/json.h>
using namespace std;
namespace wd
{
//-ljson
class MyJson//......
{
public:
    MyJson(){}
    MyJson(vector<pair<string , string>> jsonNode)
    :_nums(jsonNode.size())
    ,_webs(jsonNode)
    {
        _root["nums"] = Json::Value(_nums);
        Json::Value web;
        for(const auto &it:_webs)
        {
            web["title"] = it.first;
            web["summary"] = it.second;
            _root["webs"].append(web);
        }
    }
    string toStr() { Json::FastWriter fast_writer; return fast_writer.write(_root); }

private:
    Json::Value _root;
    int _nums;
    vector<pair<string,string>> _webs;
};

}

//int main()
//{
//    std::cout << "Hello world" << std::endl;
//    Json::Value root;
//    return 0;
//}

