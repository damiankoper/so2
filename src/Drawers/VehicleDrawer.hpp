#pragma once
#include "../MPK/Relation.hpp"
#include "../MPK/Vehicle.hpp"
#include "DrawerInterface.hpp"
#include <QPainter>
class VehicleDrawer : public DrawerInterface {
public:
  void setVehicle(Vehicle *inputVehicle);
  void setRelation(Relation *inputRelation);
  void draw(QPainter &painter) override;

private:
  Vehicle *vehicle = nullptr;
  Relation *relation = nullptr;
  int VEHICLE_STROKE = 16;
  int VEHICLE_CAPACITY_SIZE = 2;
};