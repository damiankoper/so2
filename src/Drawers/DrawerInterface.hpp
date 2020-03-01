#pragma once
#include <QPainter>

class DrawerInterface
{
public:
    virtual ~DrawerInterface(){};

    virtual void draw(QPainter &painter) = 0;
};