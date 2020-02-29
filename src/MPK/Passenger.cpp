#include "Passenger.hpp"

Passenger &Passenger::operator=(const Passenger &passenger)
{
    return *this = Passenger(passenger);
}
