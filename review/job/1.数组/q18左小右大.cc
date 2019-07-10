#include <iostream>
#include <cstdio>
using namespace std;
void solution(int *array,int length)
{
    int *rightmin = (int *) malloc(sizeof(int) * (length + 1));
    int min = array[length - 1];
    for(int i = length-1 ; i >= 0;--i)
    {
        if(array[i] < min)
            min = array[i];
        rightmin[i] = min;
    }
    int max = array[0];
    for(int i = 0;i<length -1;++i)
    {
        if(rightmin[i] >= array[i])
        {
            if(max <= array[i])
            {
                cout << "ans: " << array[i] << endl;
            }
        }
        if(max < array[i])
            max = array[i]; 
    }
    cout << "end" << endl;
}
int main()
{
    std::cout << "Hello world" << std::endl;
    int a[10] = {4,3,4,5,6,7,8,9,10,11};
    solution(a,10);
    return 0;
}

