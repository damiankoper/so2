#include "VehicleDrawer.hpp"
#include <QString>
void VehicleDrawer::setVehicle(Vehicle *inputVehicle) {
  this->vehicle = inputVehicle;
}

void VehicleDrawer::setRelation(Relation *inputRelation) {
  this->relation = inputRelation;
}

void VehicleDrawer::draw(QPainter &painter) {
  // W sumie useless jest Vector2i jak jest QPoint
  std::vector<QPoint> points = std::vector<QPoint>();
  auto length = 40;
  //      std::max(40, (int)vehicle->passengers.size() * VEHICLE_CAPACITY_SIZE);
  for (auto &&point :
       relation->getSubPoints(vehicle->distance - length / 2.0, length)) {
    points.emplace_back(point.x, point.y);
  }

  QPen pen(QColor(relation->color.c_str()).lighter(125), VEHICLE_STROKE,
           Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin);
  painter.setPen(pen);
  std::string text = std::to_string(vehicle->passengers.size());

  painter.drawPolyline(points.data(), points.size());

  int width = 30;
  int height = 15;
  int yShift = 15;
  int padding = 6;
  QColor bT = Qt::black;
  bT.setAlphaF(0.2);
  QColor wT = Qt::white;
  wT.setAlphaF(0.8);

  QPoint point = points[points.size() - 1] + QPoint(20, 20);
  QPoint pointLineStart = points[points.size() - 1];
  painter.setPen(bT);
  painter.setBrush(wT);
  painter.drawRect(point.x(), point.y() - height + yShift, width + padding,
                   height + padding);
  painter.setBrush(Qt::transparent);
  painter.drawText(point.x() + padding / 2,
                   point.y() - height + padding / 2 + yShift, width + padding,
                   height + padding, Qt::AlignLeft, QString(text.c_str()));

  QPen penLine(bT, 3, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(penLine);
  painter.drawLine(point, pointLineStart);
  painter.setPen(pen);
}