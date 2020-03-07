#pragma once

#include <vector>

class Passenger;

class Vehicle {
public:
  explicit Vehicle(float speed = 1, int capacity = 20);

  std::vector<Passenger *> passengers = std::vector<Passenger *>();

  void resetDistance();

  bool addPassenger(Passenger *newPassenger);
  bool removePassenger(Passenger *passengerToRemove);
  void incrementDistance();

  int remainingCapacity();

  float speed;
  int capacity;
  float distance = 0;
};