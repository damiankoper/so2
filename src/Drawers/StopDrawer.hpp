#pragma once
#include "DrawerInterface.hpp"
#include "../MPK/Stop.hpp"
#include <QPainter>
class StopDrawer : public DrawerInterface
{
public:
    void setStop(Stop *stop);
    void draw(QPainter &painter) override;

private:
    Stop *stop = nullptr;
    int STOP_SIZE = 25;
    int STOP_STROKE = 8;
};