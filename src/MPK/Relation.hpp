#pragma once
#include <vector>
#include <string>
#include "Stop.hpp"
#include "Passenger.hpp"
class Relation
{
public:
    std::string name;
    std::vector<Stop *> stops = std::vector<Stop *>();
    std::vector<Passenger *> passengers = std::vector<Passenger *>();
};