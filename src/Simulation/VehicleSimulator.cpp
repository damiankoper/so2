
#include "VehicleSimulator.hpp"

#include <iostream>
#include <utility>

VehicleSimulator::VehicleSimulator(Vehicle *vehicle, Relation *relation) {
  this->vehicle = vehicle;
  this->relation = relation;
}

void VehicleSimulator::run() {
  float lastStopDistance = -1;
  float totalRelationDistance = this->relation->getTotalDistance();
  while (!is_join_requested) {
    this->vehicle->incrementDistance();
    std::cout << "Vehicle distance: " << vehicle->distance << std::endl;

    // Handle cycle reset
    if (this->vehicle->distance > totalRelationDistance) {
      this->vehicle->resetDistance();
      lastStopDistance = -1;
    }

    for (auto stop : relation->stops) {
      if (lastStopDistance > relation->getStopDistance(stop)) {
        continue;
      }
      lastStopDistance = this->vehicle->distance;
      std::cout << "Vehicle stopping at '" << stop->name << "'." << std::endl;
      // Vehicle reached current stop.
      stop->mutex.lock();

      // Drop off passengers whose target is the current stop.
      // Dropped off Passenger objects are destroyed.
      for (auto passenger : this->vehicle->passengers) {
        if (passenger->target == stop) {
          this->vehicle->removePassenger(passenger);
//          delete passenger;
          this->sleep_millis(500);
        }
      }

      // Get passengers who can get to their target using this relation.
      auto availablePassengersAtStop =
          stop->getPassengersByRelation(relation);
      unsigned int boardingPassengerCount =
          availablePassengersAtStop.size() %
          (this->vehicle->remainingCapacity() + 1);
      for (int i = 0; i < boardingPassengerCount; ++i) {
        Passenger *currentPassenger = availablePassengersAtStop[i];
        this->vehicle->addPassenger(currentPassenger);
        stop->removePassenger(currentPassenger);
      }
      // Simulate passenger exchange waiting time
      this->sleep_millis(SLEEP_STOP_MILLIS);

      stop->mutex.unlock();
    }
    this->sleep_millis(SLEEP_INTERVAL_MILLIS_60FPS);
  }
}
