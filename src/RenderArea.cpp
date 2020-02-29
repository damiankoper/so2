#include "RenderArea.hpp"
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
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (auto stop : world->stops)
    {
        QPen pen(Qt::black, STOP_STROKE, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
        painter.setPen(pen);

        std::string text = std::to_string(stop->passengers.size()) + "  " + stop->name;

        int centerDelta = STOP_SIZE / 2;
        QRect rect = QRect(
            stop->position.x - centerDelta,
            stop->position.y - centerDelta,
            STOP_SIZE,
            STOP_SIZE);
        painter.drawRect(rect);
        painter.drawText(stop->position.x - centerDelta - STOP_STROKE / 2,
                         stop->position.y - (centerDelta + STOP_STROKE), tr(text.c_str()));
    }
}
