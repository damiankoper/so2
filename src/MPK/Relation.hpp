#pragma once

#include "../Geometry/Vector2i.hpp"
#include "Passenger.hpp"
#include "Stop.hpp"
#include "Vehicle.hpp"
#include <string>
#include <utility>
#include <vector>

class Stop;

class Vehicle;

class Relation {
public:
  explicit Relation(std::string name, std::string color = "red");

  std::string name;
  std::string color;
  std::vector<Stop *> stops = std::vector<Stop *>();
  std::vector<Vehicle *> vehicles = std::vector<Vehicle *>();

  std::vector<Vector2i> getPoints();

  std::vector<Vector2i> getSubPoints(int start, int length);

  Vector2i addPointsForPositions(std::vector<Vector2i> &points,
                                 const Vector2i &from, const Vector2i &to,
                                 Vector2i toOutputDirection);

  void addStop(Stop *stop, bool count = true);

  float getStopDistance(Stop *targetStop);
};