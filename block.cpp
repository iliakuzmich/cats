#include "block.h"

block::block(QObject *parent)
    : QObject{parent}
{
    x = 0;
    y = 0;
}

block::block(block const &a){
    x = a.x;
    y = a.y;
}

void block::setpos(int X, int Y)
{
    x = X;
    y = Y;
}

platform::platform(QObject *parent)
    : QObject{parent}
{
    x = 0;
    y = 0;
}

platform::platform(platform const &a){
    x = a.x;
    y = a.y;
}

void platform::setpos(int X, int Y)
{
    x = X;
    y = Y;
}
