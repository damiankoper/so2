#include "VehicleDrawer.hpp"
#include <QString>
void VehicleDrawer::setVehicle(Vehicle *vehicle) { this->vehicle = vehicle; }

void VehicleDrawer::setRelation(Relation *relation) {
  this->relation = relation;
}

void VehicleDrawer::draw(QPainter &painter) {
  // W sumie useless jest Vector2i jak jest QPoint
  std::vector<QPoint> points = std::vector<QPoint>();

  for (auto &&point : relation->getSubPoints(
           vehicle->distance, std::max(40, (int)vehicle->passengers.size() *
                                               VEHICLE_CAPACITY_SIZE))) {
    points.push_back(QPoint(point.x, point.y));
  }

  QPen pen(QColor(relation->color.c_str()).lighter(125), VEHICLE_STROKE,
           Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin);
  painter.setPen(pen);
  std::string text = std::to_string(vehicle->passengers.size());

  painter.drawPolyline(points.data(), points.size());

  int width = 30;
  int height = 15;
  int padding = 6;
  QPoint point = points[points.size() - 1] + QPoint(20, -20);
  QPoint pointLineStart = points[points.size() - 1];
  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);
  painter.drawRect(point.x(), point.y() - height,
                   width + padding, height + padding);
  painter.setBrush(Qt::transparent);
  painter.drawText(point.x() + padding / 2, point.y() - height + padding / 2,
                   width + padding, height + padding, Qt::AlignLeft,
                   QString(text.c_str()));
  QPen penLine(Qt::darkGray, 3, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(penLine);
  painter.drawLine(point, pointLineStart);
  painter.setPen(pen);
}