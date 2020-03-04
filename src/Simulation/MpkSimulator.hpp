#pragma once

#include "StopSimulator.hpp"
#include "VehicleSimulator.hpp"
#include <memory>

class MpkSimulator {
public:
  MpkSimulator();

  void createStopSimulatorsFromRelation(std::shared_ptr<Relation> relation);

  std::vector<std::shared_ptr<StopSimulator>> stopSimulators;
  std::vector<std::shared_ptr<VehicleSimulator>> vehicleSimulators;
};
