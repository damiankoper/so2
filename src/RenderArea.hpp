#pragma once
#include "MPK/MPKWorld.hpp"
#include <QWidget>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent);
    void setMPKWorld(MPKWorld *world);

protected:
    MPKWorld *world = nullptr;
    void paintEvent(QPaintEvent * /* event */);
};