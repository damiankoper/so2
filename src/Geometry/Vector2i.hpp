#pragma once
class Vector2i
{
public:
    Vector2i(int x, int y) : x(x), y(y){};
    Vector2i(const Vector2i &v) : Vector2i(v.x, v.y){};
    Vector2i &operator=(const Vector2i &v);

    int x = 0;
    int y = 0;

    Vector2i add(const Vector2i &v);
};