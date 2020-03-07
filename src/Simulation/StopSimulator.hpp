//
// Created by maja on 04.03.2020.
//

#ifndef SO2_STOPSIMULATOR_HPP
#define SO2_STOPSIMULATOR_HPP

#include "../MPK/Stop.hpp"
#include "Thread.hpp"
#include <memory>
#include <src/Utils/RandUtils.hpp>
#include <utility>

#define SPAWN_COUNT_PER_RELATION 5

class StopSimulator : public Thread {
public:
  explicit StopSimulator(Stop *stop, std::vector<Relation *> relations);

  void run() override;
  void spawnPassenger();
  std::vector<Stop *> getAvailableTargetStops();
  Stop *stop;
  std::vector<Relation *> relations;
};

#endif // SO2_STOPSIMULATOR_HPP
