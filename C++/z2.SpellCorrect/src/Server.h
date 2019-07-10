#pragma once
#include "Macro.h"
#include "Reactor.h"
namespace wd
{

class server
{

public:
    server() {}
    ~server() {}
private:
    Reactor _main_reactor;//主反应器用来监听是否有新的客户端连接进来
    Reactor _sub_reactor;//附反应器用来轮询监听已连接客户端发送过来的单词
};






}
