#include "Stop.hpp"

Stop &Stop::operator=(const Stop &stop) {
  *this = Stop(stop);
  return *this;
}

void Stop::addPassenger(Passenger *passenger) {
  this->passengers.push_back(passenger);
}

std::vector<Passenger *> Stop::getPassengersByRelation(Relation *relation) {
  // Returns passengers from this currentStop, that can get to their target
  // using this relation.
  std::vector<Passenger *> result;
  for (auto currentPassenger : this->passengers) {
    for (int i = 0; i < relation->stops.size() - 1; ++i) {
      Stop *currentStop = relation->stops[i];
      if (currentPassenger->target == currentStop) {
        // Passenger can get to target by using this relation
        result.push_back(currentPassenger);
      }
    }
  }

  return result;
}

bool Stop::removePassenger(Passenger *passengerToRemove) {
  // Attempts to remove passenger from currentStop.
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
