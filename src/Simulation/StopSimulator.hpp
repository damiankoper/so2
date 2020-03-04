//
// Created by maja on 04.03.2020.
//

#ifndef SO2_STOPSIMULATOR_HPP
#define SO2_STOPSIMULATOR_HPP

#include "../MPK/Stop.hpp"
#include "Thread.hpp"
#include <memory>

class StopSimulator : public Thread {
public:
  void run() override;
  void spawnPassengers(
      int passengerCount = 10); // TODO random passenger count generation
  std::shared_ptr<Stop> stop;
};

#endif // SO2_STOPSIMULATOR_HPP
