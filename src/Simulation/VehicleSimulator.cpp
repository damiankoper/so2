
#include "VehicleSimulator.hpp"

#include <utility>

VehicleSimulator::VehicleSimulator(std::shared_ptr<Vehicle> vehicle,
                                   std::shared_ptr<Relation> relation) {
  this->vehicle = std::move(vehicle);
  this->relation = std::move(relation);
}

void VehicleSimulator::run() {
  float lastStopDistance = -1;
  while (!is_join_requested) {
    this->vehicle->incrementDistance();

    // Handle cycle reset
    if (this->vehicle->distance > this->relation->getTotalDistance()) {
      this->vehicle->resetDistance();
      lastStopDistance = -1;
    }

    int exchangedPassengerCount = 0;

    for (auto stop : relation->stops) {
      if (lastStopDistance > relation->getStopDistance(stop)) {
        continue;
      }
      // Vehicle reached current stop.
      stop->mutex.lock();

      // Drop off passengers whose target is the current stop.
      // Dropped off Passenger objects are destroyed.
      for (auto passenger : this->vehicle->passengers) {
        if (passenger->target == stop) {
          this->vehicle->removePassenger(passenger);
          delete passenger;
          exchangedPassengerCount++;
        }
      }

      // Get passengers who can get to their target using this relation.
      auto availablePassengersAtStop =
          stop->getPassengersByRelation(relation.get());
      unsigned int boardingPassengerCount =
          availablePassengersAtStop.size() %
          (this->vehicle->remainingCapacity() + 1);
      for (int i = 0; i < boardingPassengerCount; ++i) {
        Passenger *currentPassenger = availablePassengersAtStop[i];
        this->vehicle->addPassenger(currentPassenger);
        stop->removePassenger(currentPassenger);
      }
      exchangedPassengerCount += int(boardingPassengerCount);

      // Simulate passenger exchange waiting time
      this->sleep_millis(SLEEP_STOP_MILLIS +
                         SLEEP_PER_PASSENGER_EXCHANGE_MILLIS *
                             exchangedPassengerCount);

      stop->mutex.unlock();
      break;
    }
    this->sleep_millis(SLEEP_INTERVAL_MILLIS_60FPS);
  }
}
