#include "Stop.hpp"

Stop &Stop::operator=(const Stop &stop) {
  *this = Stop(stop);
  return *this;
}

void Stop::addPassenger(const std::shared_ptr<Passenger> &passenger) {
  this->passengers.push_back(
      passenger.get()); // TODO: refactor using shared pointers
}

std::vector<Passenger *> Stop::getPassengersByRelation(Relation *relation) {
  // Returns passengers from this stop, that can get to their target using this
  // relation.
  std::vector<Passenger *> result;

  for (auto passenger : this->passengers) {
    for (auto stop : relation->stops) {
      if (passenger->target == stop) {
        // Passenger can get to target by using this relation
        result.push_back(passenger);
      }
    }
  }

  return result;
}

bool Stop::removePassenger(Passenger *passengerToRemove) {
  // Attempts to remove passenger from stop.
  // The Passenger object is NOT destroyed.
  // Returns true if passenger is found and removed.
  // Returns false otherwise.
  auto begin = passengers.begin();
  auto end = passengers.end();
  for (auto it = begin; it != end;) {
    if ((*it) == passengerToRemove) {
      this->passengers.erase(it);
      return true;
    }
    ++it;
  }
  return false;
}
