#pragma once

#include "../MPK/Vehicle.hpp"
#include "../Utils/RandUtils.hpp"
#include "Thread.hpp"
#include <map>
#include <memory>
#include <src/MPK/Relation.hpp>

#define SLEEP_PER_PASSENGER_EXCHANGE 250
#define SLEEP_ON_STOP 1000

class VehicleSimulator : public Thread {
public:
  explicit VehicleSimulator(Vehicle *vehicle, Relation *relation);

  void run() override;

  void getPassengersFromStop(Stop *stop);
  void dropPassengersAtStop(Stop *stop);
  Vehicle *vehicle;
  Relation *relation;
};
