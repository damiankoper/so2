#pragma once
#include "../Geometry/Vector2i.hpp"
#include "Stop.hpp"
#include <string>
#include <vector>
class Stop;

class Passenger {

public:
  Passenger(const Stop *source, const Stop *target)
      : source(source), target(target) {}
  Passenger(const Passenger &passenger)
      : Passenger(passenger.source, passenger.target) {}
  Passenger &operator=(const Passenger &passenger);
  ~Passenger() = default;

  const Stop *source;
  const Stop *target;
};