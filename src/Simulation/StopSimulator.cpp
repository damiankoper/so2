//
// Created by maja on 04.03.2020.
//

#include "StopSimulator.hpp"

void StopSimulator::run() {
  this->stop->mutex.lock();
  // Spawn random amount of passengers (in a specified range)
  this->stop->mutex.unlock();
}

void StopSimulator::spawnPassengers(int passengerCount) {
  for (int i = 0; i < passengerCount; ++i) {
  }
}
