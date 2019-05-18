#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

class Node
{
public:
    Node(const char *name,int id):
        _name(new char[strlen(name)+1]()),//new的小括号用来初始化
        _id(id)
    {
        cout<<"构造函数"<<endl;
        strcpy(_name,name);//初始化表达式开空间给地址,strcpy赋值
    }
    void  operator delete(void *ret)
    {
        cout<<"operator delete 重载"<<endl;
    }
private:
    ~Node()
    {
        cout<<"析构函数"<<endl;
        delete [] _name;
    }
private:
    char *_name;
    int _id;
};

int main()
{
    Node *pNode = new Node("Mike",100);
    //Node node0("Mary",101);
    return 0;
}

