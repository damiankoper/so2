#pragma once

#include "../MPK/Vehicle.hpp"
#include "../Utils/RandUtils.hpp"
#include "Thread.hpp"
#include <map>
#include <memory>
#include <src/MPK/Relation.hpp>

#define SLEEP_INTERVAL_MILLIS_60FPS 1000 / 60
#define SLEEP_PASSENGER_EXCHANGE_MILLIS 100

class VehicleSimulator : public Thread {
public:
  explicit VehicleSimulator(std::shared_ptr<Vehicle> vehicle,
                            std::shared_ptr<Relation> relation);

  void run() override;
  std::shared_ptr<Vehicle> vehicle;
  std::shared_ptr<Relation> relation;
};
