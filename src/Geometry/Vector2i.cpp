#include "Vector2i.hpp"
#include <math.h>
Vector2i &Vector2i::operator=(const Vector2i &v)
{
    x = v.x;
    y = v.y;
    return *this;
}

float Vector2i::length()
{
    return std::sqrt(x * x + y * y);
}

Vector2i Vector2i::add(const Vector2i &v)
{
    return Vector2i(v.x + x, v.y + y);
}

Vector2i Vector2i::operator-()
{
    return Vector2i(-x, -y);
}