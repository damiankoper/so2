#include "RenderArea.hpp"
#include "Drawers/RelationDrawer.hpp"
#include "Drawers/StopDrawer.hpp"
#include "Drawers/VehicleDrawer.hpp"
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <string>
RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {
  this->setGeometry(0, 0, 1280, 720);
  QPalette pal = palette();

  // set background
  pal.setColor(QPalette::Background, QColor("#DDDDDD"));
  this->setAutoFillBackground(true);
  this->setPalette(pal);

  QTimer *timer = new QTimer(this);
  QWidget *self = this;
  connect(timer, &QTimer::timeout, this, [self]() {
    for (auto &&relation : ((RenderArea *)self)->world->relations) {
      for (auto &&vehicle : relation->vehicles) {
//        vehicle->distance += vehicle->speed; // CZEMU MNIE TROLUJESZ DANUN
        // SZUKAM OD 15 MIN CZEMU WĄTEK MI ZWIĘKSZA DISTANCE KIEDY ŚPI XD
      }
    }
    self->repaint();
  });
  timer->start(1000 / 60);
}

void RenderArea::setMPKWorld(MPKWorld *mpkWorld) { this->world = mpkWorld; }

void RenderArea::paintEvent(QPaintEvent * /* event */) {
  StopDrawer stopDrawer;
  RelationDrawer relationDrawer;
  VehicleDrawer vehicleDrawer;

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  for (auto relation : world->relations) {
    relationDrawer.setRelation(relation);
    relationDrawer.draw(painter);
  }

  for (auto relation : world->relations) {
    for (auto vehicle : relation->vehicles) {
      vehicleDrawer.setRelation(relation);
      vehicleDrawer.setVehicle(vehicle);
      vehicleDrawer.draw(painter);
    }
  }

  for (auto stop : world->stops) {
    stopDrawer.setStop(stop);
    stopDrawer.draw(painter);
  }
}
