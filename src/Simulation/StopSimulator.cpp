#include "StopSimulator.hpp"

#include <utility>

StopSimulator::StopSimulator(Stop *stop, std::vector<Relation *> relations) {
  this->stop = stop;
  this->relations = std::move(relations);
  this->availableTargetStops = this->getAvailableTargetStops();
}

void StopSimulator::run() {
  while (!isJoinRequested) {
    this->stop->mutex.lock();

    // Spawn passengers on this currentStop.
    int maxSpawnCount =
        StopSimulator::spawn_count_per_relation * RandUtils::getInt(1, 10);
    int passengerCountToSpawn = RandUtils::getInt(0, maxSpawnCount + 1);
    for (int i = 0; i < passengerCountToSpawn; ++i) {
      this->spawnPassenger();
      this->sleep_millis(sleep_frame);
    }

    this->stop->mutex.unlock();

    auto sleepTime = Thread::sleep_frame * 60 * RandUtils::getInt(3, 20);
    this->sleep_millis(sleepTime);
  }
}

std::vector<Stop *> StopSimulator::getAvailableTargetStops() {
  std::vector<Stop *> result;
  // Get all possible targets using this currentStop's relations.
  for (const auto &currentRelation : this->relations) {
    for (auto currentStop : currentRelation->stops) {
      bool isStopAlreadyHandled =
          !result.empty() &&
          std::find(result.begin(), result.end(), currentStop) != result.end();
      if (this->stop == currentStop || isStopAlreadyHandled) {
        continue;
      }
      result.push_back(currentStop);
    }
  }

  return result;
}

void StopSimulator::spawnPassenger() {
  auto targetStops = this->availableTargetStops;
  if (targetStops.empty()) {
    return;
  }
  int targetIndex = RandUtils::getInt(0, targetStops.size());
  Stop *targetStop = targetStops[targetIndex];

  auto newPassenger = new Passenger(this->stop, targetStop);
  this->stop->addPassenger(newPassenger);
}
