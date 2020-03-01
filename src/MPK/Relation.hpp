#pragma once
#include <vector>
#include <string>
#include "Stop.hpp"
#include "Passenger.hpp"
class Relation
{
public:
    Relation(std::string name, std::string color = "red") : name(name), color(color){};

    std::string name;
    std::string color;
    std::vector<Stop *> stops = std::vector<Stop *>();
    std::vector<Passenger *> passengers = std::vector<Passenger *>();

    std::vector<Vector2i> getPoints(int nth = 0);
    Vector2i addPointsForPositions(std::vector<Vector2i> &points,
                                   Vector2i from,
                                   Vector2i to,
                                   Vector2i toOutputDirection);

    //Vector2i getNthShift(int nth);

    void addStop(Stop *stop, bool count = true);
};