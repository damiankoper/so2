#pragma once

#include "../Geometry/Vector2i.hpp"
#include "Passenger.hpp"
#include "Relation.hpp"
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

class Passenger;

class Relation;

class Stop {

public:
  Stop(const Vector2i &position, std::string name)
      : position(position), name(std::move(name)) {}

  Stop(const Stop &stop) : Stop(stop.position, stop.name) {}

  Stop &operator=(const Stop &stop);

  ~Stop() = default;

  void addPassenger(Passenger *passenger);

  bool removePassenger(Passenger *passengerToRemove);

  std::vector<Passenger *> getPassengersByRelation(Relation *relation);

  std::string name;
  Vector2i position;
  std::vector<Passenger *> passengers = std::vector<Passenger *>();
  std::vector<Relation *> relations = std::vector<Relation *>();
  std::shared_timed_mutex mutex;
};