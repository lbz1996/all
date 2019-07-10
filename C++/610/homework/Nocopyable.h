#pragma once

namespace wd
{

class Nocopyable
{
    //子类可以访问,基类不允许访问
protected:
    Nocopyable() {}
    ~Nocopyable() {}
    //禁止复制
    Nocopyable(const Nocopyable &) = delete;
    Nocopyable & operator = (const Nocopyable &) = delete;
};


}
