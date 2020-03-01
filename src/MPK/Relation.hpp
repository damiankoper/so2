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

    std::vector<Vector2i> getPoints();
};