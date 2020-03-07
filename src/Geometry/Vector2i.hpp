#pragma once
class Vector2i {
public:
  Vector2i() = default;
  Vector2i(int x, int y) : x(x), y(y){};
  Vector2i(const Vector2i &v) : Vector2i(v.x, v.y) { int xd = 2; };
  Vector2i &operator=(const Vector2i &v);
  bool operator==(const Vector2i &v);

  int x = 0;
  int y = 0;

  float length();

  Vector2i add(const Vector2i &v);
  Vector2i sub(const Vector2i &v);
  Vector2i operator-();
};