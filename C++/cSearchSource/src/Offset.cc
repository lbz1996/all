#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
namespace wd
{
class OffsetNode
{
public:
    OffsetNode(long docid,long begin,long length):_docid(docid),_begin(begin),_length(length) {  }
public:
    long _docid;
    long _begin;
    long _length;
};

class Offset
{
public:
    Offset(const string path_offset = "/home/lbz/github/all/C++/SearchSource/data/offset.lib"):_path_offset(path_offset)
    {
        ifstream offset_in(path_offset);
        if(offset_in.good())        
        {
            long docid,begin,length;
            //while(offset_in.eof())
            //while(offset_in.peek() != EOF)//.......
            while(true)
            {
                offset_in >> docid >> begin >> length;
                if(offset_in.eof())
                    break;
                else
                    _offset.push_back(OffsetNode(docid,begin,length));//......
            }
            cout << "_offset.size() is " << _offset.size() << endl;
        }
        else
        {
            cout << "wrong in Offset()" << endl;
        }
        offset_in.close();
    }
    long Get_OffsetLength() const { return _offset.size(); }
    OffsetNode GetX_OffsetNode (unsigned long docid) const//......
    {
        if(docid < _offset.size())
            return _offset[docid];
        else
        {
            cout << "wrong in GetX_OffsetNode()" << endl;
            return OffsetNode(-1,-1,-1);//......
        }
    }
    void read()
    {
        for(unsigned long i=0 ;i!=_offset.size();++i)
        {
            wd::OffsetNode node1 = GetX_OffsetNode(i);
            cout << node1._docid << " " << node1._begin << " " << node1._length << endl;
        }
    }
private:
    string _path_offset;
    vector<OffsetNode> _offset;
};

}
//int main()
//{
//    wd::Offset offset1;
//    offset1.read();
//    return 0;
//}
