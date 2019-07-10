#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <hash_map>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        int &&length = nums.size();
        //for(int i=0;i < length;++i) //!=时间一样,内存占用会变高
        //    for(int j=i+1;j < length;++j) 
        //        if(target == nums[i] + nums[j])
        //            return vector<int>{i, j};
        //无序容器还慢一点
        //unordered_map<int,int> out;
        //用map快,但内存占用高
        map<int,int> out;
        for(int i=0; i < length;++i)
        {
            if(out.find(target-nums[i]) != out .end())
                return vector<int>{out[target - nums[i]]+1,i+1};
            out[nums[i]] = i;
        }
        return vector<int>{};
    }
};
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

