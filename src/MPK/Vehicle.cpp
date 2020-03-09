#include "Vehicle.hpp"
#include <src/Utils/RandUtils.hpp>

Vehicle::Vehicle()
    : Vehicle(RandUtils::getFloat(SPEED_MIN, SPEED_MAX),
              RandUtils::getInt(CAPACITY_MIN, CAPACITY_MAX + 1)) {}

Vehicle::Vehicle(float speed, int capacity)
    : speed(speed), capacity(capacity) {}

bool Vehicle::addPassenger(Passenger *newPassenger) {
  if (this->remainingCapacity() == 0) {
    return false;
  }
  this->passengers.emplace_back(newPassenger);
  return true;
}

int Vehicle::remainingCapacity() {
  return this->capacity - int(this->passengers.size());
}

bool Vehicle::removePassenger(Passenger *passengerToRemove) {
  // Attempts to remove passenger from vehicle.
  // The Passenger object is NOT destroyed.
  // Returns true if passenger is found and removed.
  // Returns false otherwise.
  for (int i = 0; i < passengers.size(); ++i) {
    if (passengers[i] == passengerToRemove) {
      this->passengers.erase(passengers.begin() + i);
      return true;
    }
  }
  return false;
}
