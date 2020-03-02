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

private:
    int speed;
    int capacity;
    float distance = 0;

};