#pragma once

#include "StopSimulator.hpp"
#include "VehicleSimulator.hpp"
#include <memory>

class MpkSimulator {
public:
  explicit MpkSimulator(const std::vector<Relation *> &relations);

  void startSimulation();
  void stopSimulation();

  std::vector<std::shared_ptr<StopSimulator>> stopSimulators;
  std::vector<std::shared_ptr<VehicleSimulator>> vehicleSimulators;
};
