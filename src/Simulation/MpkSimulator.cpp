//
// Created by maja on 02.03.2020.
//

#include "MpkSimulator.hpp"
MpkSimulator::MpkSimulator(const std::vector<Relation *> &relations) {
  std::vector<Stop *> handledStops;
  std::map<Stop *, std::vector<Relation *>> relationsPerStop;

  // Map relations to each stop
  for (auto currentRelation : relations) {
    for (auto currentStop : currentRelation->stops) {
      relationsPerStop[currentStop].push_back(currentRelation);
    }
  }

  for (auto relation : relations) {
    // Create currentStop simulators for each currentStop in relation.
    // Skip creation if currentStop already has simulator.
    for (auto currentStop : relation->stops) {
      if (std::find(handledStops.begin(), handledStops.end(), currentStop) !=
          handledStops.end()) {
        continue;
      }
      auto newStopSim = std::make_shared<StopSimulator>(
          currentStop, relationsPerStop[currentStop]);
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
