#ifndef __HEAD_H__
#define __HEAD_H__
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <deque>
using namespace std;

#define RED_BLUE (_rb==0?" red ":" blue ")
//dragon、ninja、iceman、lion、wolf
char warriors[5][20]={"dragon","ninja","iceman","lion","wolf"};
char weapons[3][20]={"sword","bomb","arrow"};
//000:00 blue dragon 1 born
#define PRI_BORN()\
{\
    print_time();\
    cout<<RED_BLUE<< warriors[type] << " " << _warrior_id << " born" << endl;\
}\

#define PRI_GO(str)\
{\
    print_time();\
    cout << (warrior0->get_rb()? " blue ":" red ") \
    << warriors[warrior0->get_type()] << " " \
    << warrior0->get_id() << str \
    << _pcityArray[i]->show_id() << " with " \
    << warrior0->get_elements() << " elements " << endl;\
}\

#define PRI_TAKON(str)\
{\
    print_time();\
    cout<< str << " headquarter was taken " << endl;\
}\

int M,N,K,T;
int time_now_min= 0;
int H[5];
int A[5];
inline void print_time() { printf("%03d:%02d ",time_now_min/60,time_now_min%60); }

#include "weapon.cc"
#include "warrior.cc"
#include "city.cc"
#include "path.cc"

#endif


