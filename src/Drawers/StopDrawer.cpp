#include "StopDrawer.hpp"
#include <QString>
void StopDrawer::setStop(Stop *stop)
{
    this->stop = stop;
}

void StopDrawer::draw(QPainter &painter)
{
    QPen pen(Qt::black, STOP_STROKE, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
    painter.setPen(pen);

    std::string text = std::to_string(stop->passengers.size()) + "  " + stop->name;

    int centerDelta = STOP_SIZE / 2;
    QRect rect = QRect(
        stop->position.x - centerDelta,
        stop->position.y - centerDelta,
        STOP_SIZE,
        STOP_SIZE + std::max((stop->relationsCount - 1) * 15, 0));
    painter.drawRect(rect);
    painter.drawText(stop->position.x - centerDelta - STOP_STROKE / 2,
                     stop->position.y - (centerDelta + STOP_STROKE), QString(text.c_str()));
}