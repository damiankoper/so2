#pragma once
#include "Relation.hpp"
#include "Stop.hpp"
class MPKWorld
{
public:
    std::vector<Stop *> stops = std::vector<Stop *>();
    std::vector<Relation *> relations = std::vector<Relation *>();
};