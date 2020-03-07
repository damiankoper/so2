#pragma once

#include <vector>

#define SPEED_MIN 0.5
#define SPEED_MAX 2

#define CAPACITY_MIN 20
#define CAPACITY_MAX 40

class Passenger;

class Vehicle {
public:
  explicit Vehicle(float speed, int capacity);
  Vehicle();
  std::vector<Passenger *> passengers = std::vector<Passenger *>();

  bool addPassenger(Passenger *newPassenger);
  bool removePassenger(Passenger *passengerToRemove);

  int remainingCapacity();

  float speed;
  int capacity;
  float distance = 0;
};