#pragma once
#include "MPK/MPKWorld.hpp"
#include <QWidget>

class RenderArea : public QWidget {
Q_OBJECT

public:
    explicit RenderArea(QWidget *parent);

    void setMPKWorld(MPKWorld *mpkWorld);

protected:
    MPKWorld *world = nullptr;

    void paintEvent(QPaintEvent * /* event */) override;
};