#pragma once

#include "../MPK/Vehicle.hpp"
#include "../Utils/RandUtils.hpp"
#include "Thread.hpp"
#include <map>
#include <memory>
#include <src/MPK/Relation.hpp>

class VehicleSimulator : public Thread {
public:
  explicit VehicleSimulator(Vehicle *vehicle, Relation *relation);

  void run() override;

  int getPassengersFromStop(Stop *stop);
  int dropPassengersAtStop(Stop *currentStop);
  void updateDistance();

  float lastStopDistance;
  Vehicle *vehicle;
  Relation *relation;

  static const unsigned long sleep_on_stop = Thread::sleep_frame * 60;
  static const unsigned long sleep_per_passenger_exchange =
      Thread::sleep_frame * 15;
};
