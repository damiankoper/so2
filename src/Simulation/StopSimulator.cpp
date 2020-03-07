#include "StopSimulator.hpp"

#include <utility>

StopSimulator::StopSimulator(Stop *stop, std::vector<Relation *> relations) {
  this->stop = stop;
  this->relations = std::move(relations);
}

void StopSimulator::run() {
  while (!isJoinRequested) {
    this->stop->mutex.lock();

    // Spawn passengers on this stop.
    int maxSpawnCount = SPAWN_COUNT_PER_RELATION * this->relations.size();
    int passengerCountToSpawn = RandUtils::getInt(0, maxSpawnCount);
    for (int i = 0; i < passengerCountToSpawn; ++i) {
      this->spawnPassenger();
      this->sleep_millis(SLEEP_INTERVAL_FRAME);
    }

    this->stop->mutex.unlock();

    auto sleepTime = 1000 * RandUtils::getInt(5, 20);
    this->sleep_millis(sleepTime);
  }
}

std::vector<Stop *> StopSimulator::getAvailableTargetStops() {
  std::vector<Stop *> availableTargetStops;
  // Get all possible targets using this stop's relations.
  for (const auto &currentRelation : this->relations) {
    for (auto currentStop : currentRelation->stops) {
      if (this->stop == currentStop ||
          std::find(availableTargetStops.begin(), availableTargetStops.end(),
                    currentStop) != availableTargetStops.end()) {
        continue;
      }
      availableTargetStops.push_back(currentStop);
    }
  }

  return availableTargetStops;
}

void StopSimulator::spawnPassenger() {
  auto availableTargetStops = this->getAvailableTargetStops();
  if (availableTargetStops.empty()) {
    return;
  }
  int targetIndex = RandUtils::getInt(0, availableTargetStops.size());
  Stop *targetStop = availableTargetStops[targetIndex];

  auto newPassenger = new Passenger(this->stop, targetStop);
  this->stop->addPassenger(newPassenger);
}
