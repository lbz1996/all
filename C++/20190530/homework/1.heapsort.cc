#include <iostream>
#include <cmath>
using namespace std;
#define SWAP(a,b) \
{\
    T temp = _parr[a];_parr[a] = _parr[b];_parr[b] = temp;\
}
#define PRINT() \
{\
    for(auto it:arr)\
    cout<<it<<" ";\
    cout<<endl;\
}
template <typename T, typename Compare = std::less<T> >
class HeapSort
{
public:
    HeapSort(T * arr, int size):_parr(arr),_size(size) { sort(); }
    void heapAdjust(int end)
    {
        int j1,j2;
        for(int i=0;i<end/2;++i)//=.......
        {
            j1 = i;
            while(j1<end)
            {
                if(j1*2 + 1<end)
                    j2 = j1 * 2 + 1;
                if(j1*2+2<end&&_parr[j2]<_parr[j1*2+2])
                    j2 = j1 * 2 + 2;
                if(_parr[j1] < _parr[j2])
                {
                    SWAP(j1,j2);
                    j1 = j2;
                }
                else
                    break;
            }
        }
    }
    void sort()
    {
        heapAdjust(_size);
        for(int i=0;i<_size-1;++i)
        {
            SWAP(0,_size-i-1);
            heapAdjust(_size-i-1);
        }
    }
private:
    T * _parr;
    int _size;
};

void test1()
{
    int arr[5] = {23,14,25,25,6};
    PRINT();
    HeapSort< int > (arr,5);
    PRINT();
}

class point
{
public:
    point(int x=0,int y=0):_x(x),_y(y){}
    void print()
    {
        cout<<"("<<_x<<","<<_y<<")"<<" ";
    }
    int _x;
    int _y;
};
bool operator< (const point &l,const point &r)
{
    return sqrt(l._x*l._x+l._y*l._y) < sqrt(r._x*l._x+r._y*l._y);  
}
class point_less
{
    bool operator() (const point &l,const point &r) const
    {
        return sqrt(l._x*l._x+l._y*l._y) < sqrt(r._x*l._x+r._y*l._y);  
    }
};
void test2()
{
    point p0[5];
    for(int i=0,j=5;i<5;++i,--j)
    {
        point p1(i,j);
        p0[i] = p1;
    }
    for(int i=0;i<5;++i)
        p0[i].print();
    cout<<endl;
    HeapSort<point,point_less>(p0,5);
    for(int i=0;i<5;++i)
        p0[i].print();
    cout<<endl;
}

int main()
{
    test1();
    test2();
    return 0;
}

