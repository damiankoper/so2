#include "StopSimulator.hpp"

StopSimulator::StopSimulator(std::vector<std::shared_ptr<Relation>> relations) {
  this->relations = std::move(relations);
}

void StopSimulator::run() {
  this->stop->mutex.lock();

  // Spawn random amount of passengers on this stop.
  int maxSpawnCount = SPAWN_COUNT_PER_RELATION * this->relations.size();
  int passengerCountToSpawn = RandUtils::getInt(0, maxSpawnCount);
  this->spawnPassengers(passengerCountToSpawn);

  this->stop->mutex.unlock();
}

void StopSimulator::spawnPassengers(int passengerCount) {
  for (int i = 0; i < passengerCount; ++i) {
    std::shared_ptr<Passenger> newPassenger;

    auto availableTargetStops = this->getAvailableTargetStops();
    if (availableTargetStops.empty()) {
      return;
    }
    int targetIndex = RandUtils::getInt(0, availableTargetStops.size());
    Stop *targetStop = availableTargetStops[targetIndex];

    newPassenger = std::make_shared<Passenger>(this->stop.get(), targetStop);
    this->stop->addPassenger(newPassenger);
  }
}

std::vector<Stop *> StopSimulator::getAvailableTargetStops() {
  std::vector<Stop *> availableTargetStops;

  // Get all possible targets using this stop's relations.
  for (const auto &currentRelation : this->relations) {
    for (auto currentStop : currentRelation->stops) {
      if (this->stop.get() == currentStop) {
        // Ignore this stop.
        continue;
      }
      availableTargetStops.push_back(currentStop);
    }
  }

  return availableTargetStops;
}
