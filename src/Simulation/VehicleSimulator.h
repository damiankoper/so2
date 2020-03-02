#pragma once

#include "Thread.h"
#include "../MPK/Vehicle.hpp"
#define SLEEP_INTERVAL_NANOS_60FPS 1000000000/60

class VehicleSimulator : public Thread {
public:
    void run() override;
    Vehicle vehicle;
};
