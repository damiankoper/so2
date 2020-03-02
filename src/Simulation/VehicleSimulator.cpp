
#include "VehicleSimulator.h"

void VehicleSimulator::run() {
    while (!is_join_requested) {
        this->vehicle.incrementDistance();
        struct timespec tp{0, SLEEP_INTERVAL_NANOS_60FPS};
        nanosleep(&tp, nullptr);
    }
}
