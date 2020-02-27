#include "Vector2i.hpp"
Vector2i &Vector2i::operator=(const Vector2i &v)
{
    return *this = Vector2i(v);
}

Vector2i Vector2i::add(const Vector2i &v)
{
    return Vector2i(v.x + x, v.y + y);
}