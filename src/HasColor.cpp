#include "HasColor.hpp"

// Parameters to QColor::fromHsv in ranges [0, 255]
const int HasColor::kMinSaturation = 127;
const int HasColor::kMaxSaturation = 255;
const int HasColor::kMaxValue = 255;

HasColor::HasColor(const QColor& color) :
  color_{color}
{
  if (!color.isValid())
    throw std::range_error("Invalid color"); // TODO: Improve error message
}

int HasColor::randomHue() {
  // The hue is a direction in degrees, thus the range is [0, 359]
  return rand() % 360; // TODO: Use the new C++ 11 random module
}

int HasColor::randomSaturation() {
  return rand() % (kMaxSaturation - kMinSaturation + 1) + kMinSaturation;
}
