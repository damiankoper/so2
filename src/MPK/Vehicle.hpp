#pragma once

#include <vector>

class Passenger;

class Vehicle {
public:
    explicit Vehicle(int speed = 1, int capacity = 10);

    std::vector<Passenger *> passengers = std::vector<Passenger *>();

    void resetDistance();

    void addPassenger(Passenger *);

    void incrementDistance();

    int speed;
    int capacity;
    float position = 0;
};