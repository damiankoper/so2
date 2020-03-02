#pragma once
#include <vector>
class Passenger;
class Vehicle
{
public:
    /**
     * [0, relationDistance]
     */
    int position = 0;
    int speed = 1;

    int capacity = 10;
    int usage = 0;

    std::vector<Passenger*> passengers = std::vector<Passenger*>();
};