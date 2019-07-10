#include <iostream>
#include <stack>
using namespace std;
//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution 
{
public:
    bool findTarget(TreeNode* root, int k) 
    {
        int ref = 0;
        TreeNode *tmp;
        stack<TreeNode*> seq;
        seq.push(root);
        while(seq.size())
        {
            tmp = seq.top();
            seq.pop();
            if(tmp->left)
                seq.push(tmp->left);
            if(tmp->right)
                seq.push(tmp->right);
        }
    }
};
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

