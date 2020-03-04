#include "VehicleDrawer.hpp"
#include <QString>
void VehicleDrawer::setVehicle(Vehicle *vehicle) { this->vehicle = vehicle; }

void VehicleDrawer::setRelation(Relation *relation) {
  this->relation = relation;
}

void VehicleDrawer::draw(QPainter &painter) {
  // W sumie useless jest Vector2i jak jest QPoint
  std::vector<QPoint> points = std::vector<QPoint>();

  QPen pen2(Qt::darkYellow, 5, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
  painter.setPen(pen2);

  for (auto &&point : relation->getSubPoints(
           vehicle->position, std::max(40, (int)vehicle->passengers.size() *
                                               VEHICLE_CAPACITY_SIZE))) {
    points.push_back(QPoint(point.x, point.y));
    painter.drawEllipse(QPoint(point.x, point.y), 20, 20);
  }

  QPen pen(QColor(relation->color.c_str()).lighter(125), VEHICLE_STROKE,
           Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
  painter.setPen(pen);

  painter.drawPolyline(points.data(), points.size());
}