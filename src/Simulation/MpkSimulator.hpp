#pragma once

#include "StopSimulator.hpp"
#include "VehicleSimulator.hpp"
#include <memory>

class MpkSimulator {
public:
  MpkSimulator();

  void startSimulation();

  void
  initFromRelations(const std::vector<Relation *> &relations); // TODO: impl

  std::vector<std::shared_ptr<StopSimulator>> stopSimulators;
  std::vector<std::shared_ptr<VehicleSimulator>> vehicleSimulators;
};
