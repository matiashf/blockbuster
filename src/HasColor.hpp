#ifndef HAS_COLOR_HPP
#define HAS_COLOR_HPP

#include <QColor>

/* A class for giving an object a color, with some convenience
   functions for generating random colors. */
class HasColor {
public:
  HasColor(const QColor&);
  inline const QColor& color() { return color_; }
  // Set the color using copy assignment
  inline void setColor(const QColor& color) { color_ = color; }
protected:
  // We only implement what we need to achieve the behavior set out in DESIGN.md
  static int randomHue();
  static int randomSaturation();
  static const int kMinSaturation;
  static const int kMaxSaturation;
  static const int kMaxValue;
  static const int kMinValue;
private:
  QColor color_;
};

#endif
