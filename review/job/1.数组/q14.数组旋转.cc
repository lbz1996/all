#include <iostream>
#include <cstdio>
using namespace std;
#define N 12
void rotate(int array[][N])
{
    for(int dis = N,row = 0 ; N > 0 && row <= N/2;dis -= 2 , ++row)
    {
        for(int i = row; i < N ;++i)
        {
            int save = array[row][i];
            array[row][i] = array[row - i][dis];
        }
    }
}

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

