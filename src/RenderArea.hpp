#pragma once
#include "MPK/MPKWorld.hpp"
#include <QWidget>

#define STOP_SIZE 25
#define STOP_STROKE 8

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