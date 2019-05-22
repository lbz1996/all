#include "head.h"
#include "hide.cc"
int main()
{
    std::cout << "Hello world" << std::endl;
    Line_out l1(1,2,3,4);
    l1.print();

    //Line_out l2(1);//默认没啥用.....
    //l2.print();
    
    //Line_out::Line_in l3(2,2,3,4);//里面的....没藏住啊......
    //l3.printLine_in();            //前置声明放在privat就能藏住了....

    return 0;
}

