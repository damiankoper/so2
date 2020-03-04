#include "RenderArea.hpp"
#include "Drawers/StopDrawer.hpp"
#include "Drawers/RelationDrawer.hpp"
#include "Drawers/VehicleDrawer.hpp"
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <string>
RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0, 0, 1280, 720);
    QPalette pal = palette();

    // set background
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    auto *timer = new QTimer(this);
    QWidget *self = this;
    connect(timer, &QTimer::timeout, this, [self]() {
        auto v1 = ((RenderArea *)self)->world->relations[0]->vehicles[0];
        v1->position = v1->speed;
        self->repaint();
    });
    timer->start(1000 / 60);
}

void RenderArea::setMPKWorld(MPKWorld *mpkWorld) {
    this->world = mpkWorld;
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    StopDrawer stopDrawer;
    RelationDrawer relationDrawer;
    VehicleDrawer vehicleDrawer;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (auto relation : world->relations)
    {
        relationDrawer.setRelation(relation);
        relationDrawer.draw(painter);
    }

    for (auto relation : world->relations)
    {
        for (auto vehicle : relation->vehicles)
        {
            vehicleDrawer.setRelation(relation);
            vehicleDrawer.setVehicle(vehicle);
            vehicleDrawer.draw(painter);
        }
    }

    for (auto stop : world->stops)
    {
        stopDrawer.setStop(stop);
        stopDrawer.draw(painter);
    }
}
