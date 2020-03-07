#include "StopSimulator.hpp"

#include <utility>

StopSimulator::StopSimulator(Stop *stop, std::vector<Relation *> relations) {
  this->stop = stop;
  this->relations = std::move(relations);
}

void StopSimulator::run() {
  while (!is_join_requested) {
    this->stop->mutex.lock();

    // Spawn random amount of passengers on this stop.
    int maxSpawnCount = SPAWN_COUNT_PER_RELATION * this->relations.size();
    int passengerCountToSpawn = RandUtils::getInt(0, maxSpawnCount);
    for (int i = 0; i < passengerCountToSpawn; ++i) {
      this->spawnPassenger();
      this->sleep_millis(SLEEP_INTERVAL_MILLIS_60FPS);
    }

    this->stop->mutex.unlock();
    auto sleepTime = 1000 * RandUtils::getInt(2, 5);
    this->sleep_millis(sleepTime);
  }
}

std::vector<Stop *> StopSimulator::getAvailableTargetStops() {
  std::vector<Stop *> availableTargetStops;

  // Get all possible targets using this stop's relations.
  for (const auto &currentRelation : this->relations) {
    for (auto currentStop : currentRelation->stops) {
      if (this->stop == currentStop) {
        // Ignore this stop.
        continue;
      }
      availableTargetStops.push_back(currentStop);
    }
  }

  return availableTargetStops;
}
void StopSimulator::spawnPassenger() {
  std::shared_ptr<Passenger> newPassenger;

  auto availableTargetStops = this->getAvailableTargetStops();
  if (availableTargetStops.empty()) {
    return;
  }
  int targetIndex = RandUtils::getInt(0, availableTargetStops.size());
  Stop *targetStop = availableTargetStops[targetIndex];

  newPassenger = std::make_shared<Passenger>(this->stop, targetStop);
  this->stop->addPassenger(newPassenger);
}
