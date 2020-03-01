#include "RenderArea.hpp"
#include "Drawers/StopDrawer.hpp"
#include "Drawers/RelationDrawer.hpp"
#include <QPainter>
#include <QPen>
#include <string>
RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0, 0, 1280, 720);
    QPalette pal = palette();

    // set background
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void RenderArea::setMPKWorld(MPKWorld *world)
{
    this->world = world;
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    StopDrawer stopDrawer;
    RelationDrawer relationDrawer;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int c = 0;
    for (auto relation : world->relations)
    {
        relationDrawer.setRelation(relation);
        relationDrawer.setNth(c++);
        relationDrawer.draw(painter);
    }

    for (auto stop : world->stops)
    {
        stopDrawer.setStop(stop);
        stopDrawer.draw(painter);
    }
}
