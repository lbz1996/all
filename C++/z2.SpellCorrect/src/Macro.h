#pragma once
#include <cstdio>
#include <errno.h>
#include <functional>
using std::function;
bool DEBUG = true;
using FuncCallback = function<void (void*) >;
#define FUNC_ERROR_1(ret,retval,func)       \
{                                           \
    printf("%d Line->",__LINE__);           \
    if(ret==retval)                         \
    {                                       \
        perror(func);                       \
    }                                       \
    else                                    \
    {                                       \
        if(DEBUG)                           \
            printf("%s success\n",func);    \
    }                                       \
}                              
// '\'后面不要有空格
