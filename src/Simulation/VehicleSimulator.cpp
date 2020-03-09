#include "VehicleSimulator.hpp"

#include <algorithm>
#include <iostream>

VehicleSimulator::VehicleSimulator(Vehicle *vehicle, Relation *relation) {
  this->vehicle = vehicle;
  this->relation = relation;
  this->lastStopDistance = -1;
}

void VehicleSimulator::run() {
  while (!isJoinRequested) {
    this->updateDistance();

    // Vehicle stopping on currentStop
    for (int i = 0; i < relation->stops.size() - 1; ++i) {
      auto currentStop = relation->stops[i];
      // Check if vehicle should currentStop on currentStop.
      float currentStopDistance = relation->getStopDistance(currentStop);
      if (currentStopDistance <= lastStopDistance ||
          this->vehicle->distance < currentStopDistance) {
        continue;
      }

      // Vehicle reached current currentStop.
      lastStopDistance = this->vehicle->distance;

      // Perform passenger exchange
      currentStop->mutex.lock();
      this->sleep_millis(VehicleSimulator::sleep_on_stop);
      dropPassengersAtStop(currentStop);
      getPassengersFromStop(currentStop);
      this->sleep_millis(VehicleSimulator::sleep_on_stop);
      currentStop->mutex.unlock();

      break;
    }
    this->sleep_millis(sleep_frame);
  }
}

int VehicleSimulator::getPassengersFromStop(Stop *stop) {
  // Get passengers from specified currentStop, who can get to their
  // target using this vehicle's relation.
  auto availablePassengersAtStop =
      stop->getPassengersByRelation(this->relation);
  int remainingCapacity = this->vehicle->remainingCapacity();
  int availablePassengerCount = int(availablePassengersAtStop.size());
  int boardingPassengerCount =
      std::min(remainingCapacity, availablePassengerCount);

  for (int i = 0; i < boardingPassengerCount; ++i) {
    Passenger *currentPassenger = availablePassengersAtStop[i];
    this->vehicle->addPassenger(currentPassenger);
    stop->removePassenger(currentPassenger);
    this->sleep_millis(VehicleSimulator::sleep_per_passenger_exchange);
  }

  return boardingPassengerCount;
}

int VehicleSimulator::dropPassengersAtStop(Stop *currentStop) {
  // Drop off passengers whose target is the currentStop.
  int actualDropCount = 0;

  // Loop over vehicle's passengers until all passengers with currentStop as
  // target are dropped.
  while (true) {
    bool foundPassengerToRemove = false;

    for (auto passenger : this->vehicle->passengers) {
      if (passenger->target == currentStop) {
        this->vehicle->removePassenger(passenger);
        foundPassengerToRemove = true;
        //        delete passenger; // TODO: wysrywa sie, nie wiem czemu.
        ++actualDropCount;
        this->sleep_millis(VehicleSimulator::sleep_per_passenger_exchange);
      }
    }
    if (!foundPassengerToRemove) {
      break;
    }
  }

  return actualDropCount;
}

void VehicleSimulator::updateDistance() {
  bool shouldIncreaseDistance = true;

  // Vehicle distance reset on new cycle.
  if (vehicle->distance + vehicle->speed >= relation->getTotalDistance()) {
    this->vehicle->distance = 0;
    lastStopDistance = -1;
    shouldIncreaseDistance = false;
  }

  // Vehicle queueing
  for (auto otherVehicle : relation->vehicles) {
    if (this->vehicle == otherVehicle) {
      continue;
    }

    float thisDist = this->vehicle->distance;
    float otherDist = otherVehicle->distance;
    float minDistanceBetweenVehicles = 50;

    if ( // This vehicle is behind other vehicle and both are in the same cycle.
        (otherDist > thisDist &&
         otherDist - thisDist <= minDistanceBetweenVehicles) ||
        // This vehicle is behind other vehicle, but other vehicle is in
        // next cycle.
        (otherDist < thisDist &&
         relation->getTotalDistance() - thisDist + otherDist <=
             minDistanceBetweenVehicles)) {
      shouldIncreaseDistance = false;
      break;
    }
  }

  if (shouldIncreaseDistance) {
    vehicle->distance += vehicle->speed;
  }
}
