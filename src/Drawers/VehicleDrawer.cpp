#include "VehicleDrawer.hpp"
#include <QString>
void VehicleDrawer::setVehicle(Vehicle *vehicle)
{
    this->vehicle = vehicle;
}

void VehicleDrawer::setRelation(Relation *relation)
{
    this->relation = relation;
}

void VehicleDrawer::draw(QPainter &painter)
{
    QPen pen(Qt::black, VEHICLE_STROKE, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
    painter.setPen(pen);

            
}