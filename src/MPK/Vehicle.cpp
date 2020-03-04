#include "Vehicle.hpp"

void Vehicle::resetDistance() {
    this->position = 0;
}

Vehicle::Vehicle(int speed, int capacity) : speed(speed), capacity(capacity) {}

void Vehicle::addPassenger(Passenger *newPassenger) {
    if (passengers.size() == capacity) {
        throw "Vehicle is full!";
    }
    this->passengers.emplace_back(newPassenger);
}

void Vehicle::incrementDistance() {
    position += speed;
}

