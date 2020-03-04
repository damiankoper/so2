#include "RandUtils.hpp"
#include <ctime>

int RandUtils::getInt(int min, int max) {
  if (min == max) {
    return min;
  }
  int num = rand() % (max - min) + min;
  return num;
}

double RandUtils::getDouble(double min, double max) {
  if (min == max) {
    return min;
  }
  double num = (double)rand() / RAND_MAX;
  return num * (max - min) + min;
}

float RandUtils::getFloat(float min, float max) {
  if (min == max) {
    return min;
  }
  float num = (float)rand() / RAND_MAX;
  return num * (max - min) + min;
}

unsigned int RandUtils::getUInt(unsigned int min, unsigned int max) {
  if (min == max) {
    return min;
  }
  unsigned int num = rand() % (max - min) + min;
  return num;
}
