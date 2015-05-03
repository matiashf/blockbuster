#include "Colored.hpp"

// Parameters to QColor::fromHsv in ranges [0, 255]
const int Colored::kMinSaturation = 127;
const int Colored::kMaxSaturation = 255;
const int Colored::kMinValue = 64;
const int Colored::kMaxValue = 255;

Colored::Colored(const QColor& color) :
  color_{color}
{
  if (!color.isValid())
    throw std::range_error("Invalid color"); // TODO: Improve error message
}

int Colored::randomHue() {
  // The hue is a direction in degrees, thus the range is [0, 359]
  return rand() % 360; // TODO: Use the new C++ 11 random module
}

int Colored::randomSaturation() {
  return rand() % (kMaxSaturation - kMinSaturation + 1) + kMinSaturation;
}
