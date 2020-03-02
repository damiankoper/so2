#pragma once
#include "Passenger.hpp"
#include "Relation.hpp"
#include "../Geometry/Vector2i.hpp"
#include <string>
#include <vector>
class Passenger;
class Relation;

class Stop
{

public:
    Stop(Vector2i position, std::string name) : position(position), name(name) {}
    Stop(const Stop &stop) : Stop(stop.position, stop.name) {}
    Stop &operator=(const Stop &stop);
    ~Stop(){};

    std::string name;
    Vector2i position;
    std::vector<Passenger *> passengers = std::vector<Passenger *>();
    std::vector<Relation *> relations = std::vector<Relation *>();
};