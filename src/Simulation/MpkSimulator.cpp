//
// Created by maja on 02.03.2020.
//

#include "MpkSimulator.hpp"
MpkSimulator::MpkSimulator(const std::vector<Relation *> &relations) {
  std::vector<Stop *> handledStops;

  for (auto relation : relations) {
    // Create stop simulators for each stop in relation.
    // Skip creation if stop already has simulator.
    for (auto stop : relation->stops) {
      if (std::find(handledStops.begin(), handledStops.end(), stop) !=
          handledStops.end()) {
        continue;
      }
      auto newStopSim = std::make_shared<StopSimulator>(stop, relations);
      this->stopSimulators.push_back(newStopSim);
    }

    // Create vehicle simulators
    for (auto vehicle : relation->vehicles) {
      auto newVehicleSim =
          std::make_shared<VehicleSimulator>(vehicle, relation);
      this->vehicleSimulators.push_back(newVehicleSim);
    }
  }
}

void MpkSimulator::startSimulation() {
  for (const auto &stopSim : this->stopSimulators) {
    stopSim->start();
  }
  for (const auto &vehiSim : this->vehicleSimulators) {
    vehiSim->start();
  }
}

void MpkSimulator::stopSimulation() {
  // Joins all simulator threads and the returns
  for (const auto &stopSim : this->stopSimulators) {
    stopSim->join();
  }
  for (const auto &vehiSim : this->vehicleSimulators) {
    vehiSim->join();
  }
}
