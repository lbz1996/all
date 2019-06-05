#include <iostream>
#include <string>
#include <stack>
using namespace std;
//跟说明不一样....得完全匹配,右括号也得匹配....
class Solution {
public:
    bool isValid(string s)
    {
        stack<int> s1;
        if(0==s.size())
            return true;
        for(auto it:s)
        {
            if(it == '(' || it == '[' || it == '{')
                s1.push(it);
            if(it == ')' || it == ']' || it == '}')
            {
                if(s1.size())
                {
                    if(it - s1.top() == 2 || it - s1.top() == 1)
                        s1.pop();
                    else
                        return false;
                }
                else
                    return false;
            }
        }
        return !s1.size();
    }
};

int main()
{
    string str;
    Solution s1;
    while(cin>>str)
    {
        if(s1.isValid(str))
            cout<<"true"<<endl;
        else
            cout<<"false"<<endl;
    }
    return 0;
}

