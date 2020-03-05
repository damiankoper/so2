#pragma once

#include <chrono>
#include <random>

class RandUtils {
public:
  static unsigned int getUInt(unsigned int min, unsigned int max);

  static int getInt(int min, int max);

  static double getDouble(double min = 0, double max = 1);

  static float getFloat(float min, float max);
};
