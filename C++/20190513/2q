#include <iostream>
void test1()
{
    using namespace std;
    int number=1;
    int &ref=number;
    cout<<"ref    is "<<ref<<endl
        <<"number is "<<number<<endl;
    ref=2;//等于 int num2=2; ref=num2;就是赋值操作而已
    cout<<"ref    is "<<&ref<<endl
        <<"number is "<<&number<<endl;
    //取地址一样,和常量指针有什么区别???
    int *p;
    //int &ref2;//必须初始化
}
void swap(int &x,int& y)//引用传递的是实参
{
    int temp=x;
    x=y;
    y=temp;
}
//作为函数返回值时应该返回堆空间的数据
int array[5]={1,2,3,4,5};
int &index(int idx)
{
    return array[idx];
}



int main()
{
    using namespace std;
    test1();
    int x=3,y=4;
    int &px=x,&py=y;
    cout<<px<<" "<<py<<endl;
    swap(px,py);
    cout<<px<<" "<<py<<endl;

    for(int i:array)
        cout<<i<<endl;
    cout<<endl;
    index(4)=27;
    for(int i:array)
        cout<<i<<endl;
    cout<<endl;

    return 0;
}

