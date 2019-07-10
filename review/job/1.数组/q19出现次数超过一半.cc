//https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=13&tqId=11181
#include <vector>
using std::vector;
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) 
    {
        int currentNum;
        size_t currentCounts = 0;
        for(size_t i = 0 ;i < numbers.size();++i)
        {
            if(currentCounts == 0)
            {
                currentNum = numbers[i];
                currentCounts = 1;
            }
            else
            {
                if(currentNum == numbers[i])
                    ++currentCounts;
                else
                    --currentCounts;
            }
        }
        //不确定有咩有就再记一次数....
        currentCounts = 0;
        for(size_t i = 0;i < numbers.size();++i)
            if(currentNum == numbers[i])
                ++currentCounts;
        if(currentCounts > numbers.size()/2)
            return currentNum;
        else
            return 0;
    }
};
