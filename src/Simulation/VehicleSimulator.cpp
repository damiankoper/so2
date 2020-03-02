
#include "VehicleSimulator.h"

void VehicleSimulator::run() {
    while (!is_join_requested) {
        this->vehicle.distance += this->vehicle.speed;
        struct timespec tp{0, SLEEP_INTERVAL_NANOS_60FPS};
        nanosleep(&tp, nullptr);
    }
}
