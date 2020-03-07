#include "VehicleSimulator.hpp"

#include <iostream>

VehicleSimulator::VehicleSimulator(Vehicle *vehicle, Relation *relation) {
  this->vehicle = vehicle;
  this->relation = relation;
}

void VehicleSimulator::run() {
  float lastStopDistance = -1;
  float totalRelationDistance = this->relation->getTotalDistance();

  while (!isJoinRequested) {
    // Handle cycle looping
    if (vehicle->distance + vehicle->speed < totalRelationDistance) {
      vehicle->distance += vehicle->speed;
    }
    else{
      this->vehicle->distance = 0;
      lastStopDistance = -1;
    }

    for (int i = 0; i < relation->stops.size() - 1; ++i) {
      auto currentStop = relation->stops[i];

      float currentStopDistance = relation->getStopDistance(currentStop);
      if (currentStopDistance <= lastStopDistance ||
          this->vehicle->distance < currentStopDistance) {
        continue;
      }

      // Vehicle reached current stop.
      lastStopDistance = this->vehicle->distance;
      this->sleep_millis(SLEEP_ON_STOP);

      currentStop->mutex.lock();

      dropPassengersAtStop(currentStop);
      getPassengersFromStop(currentStop);

      currentStop->mutex.unlock();
      this->sleep_millis(SLEEP_ON_STOP);

      break;
    }
    this->sleep_millis(SLEEP_INTERVAL_FRAME);
  }
}

void VehicleSimulator::getPassengersFromStop(Stop *stop) {
  // Get passengers from specified stop, who can get to their
  // target using this vehicle's relation.
  auto availablePassengersAtStop =
      stop->getPassengersByRelation(this->relation);
  unsigned int boardingPassengerCount =
      availablePassengersAtStop.size() %
      (this->vehicle->remainingCapacity() + 1);

  for (int i = 0; i < boardingPassengerCount; ++i) {
    Passenger *currentPassenger = availablePassengersAtStop[i];
    this->vehicle->addPassenger(currentPassenger);
    stop->removePassenger(currentPassenger);
    this->sleep_millis(SLEEP_PER_PASSENGER_EXCHANGE);
  }
}

void VehicleSimulator::dropPassengersAtStop(Stop *stop) {
  // Drop off passengers whose target is the current stop.
  // Dropped off Passenger objects are destroyed.
  for (auto passenger : this->vehicle->passengers) {
    if (passenger->target == stop) {
      this->vehicle->removePassenger(passenger);
      //      delete passenger;
      this->sleep_millis(SLEEP_PER_PASSENGER_EXCHANGE);
    }
  }
}
