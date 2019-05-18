#include <iostream>

int main()
{
    using namespace std;
    int *point_malloc=(int *) malloc(sizeof(int));
    int *point_new=new int(10);
    int *parray=new int[10]();//会自动默认初始化...
    int *parry2=new int[10]();
    for(int i=0;i<10;++i)
    {
        cout<<parray[i]<<" ";
    }
    cout<<endl;
    free(point_malloc);
    delete [] parray;
    delete [] parry2;
    delete point_new;
    return 0;
}

