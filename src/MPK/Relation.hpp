#pragma once
#include "../Geometry/Vector2i.hpp"
#include "Passenger.hpp"
#include "Stop.hpp"
#include "Vehicle.hpp"
#include <vector>
#include <string>
class Stop;
class Vehicle;
class Relation
{
public:
    Relation(std::string name, std::string color = "red") : name(name), color(color){};

    std::string name;
    std::string color;
    std::vector<Stop *> stops = std::vector<Stop *>();
    std::vector<Vehicle *> vehicles = std::vector<Vehicle *>();

    std::vector<Vector2i> getPoints();
    std::vector<Vector2i> getSubPoints(int start, int length);
    Vector2i addPointsForPositions(std::vector<Vector2i> &points,
                                   Vector2i from,
                                   Vector2i to,
                                   Vector2i toOutputDirection);

    void addStop(Stop *stop, bool count = true);
};