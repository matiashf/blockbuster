#ifndef HAS_COLOR_HPP
#define HAS_COLOR_HPP

#include <QColor>

/** A class for giving an object a color, with some convenience
    functions for generating random colors.

    There are some visual challenges that must be solved in the game:
    1. Associating items on the scene with players.
    2. Distinguishing between boxes, so that two boxes next to each
       other do not appear to be one single box.
    3. Indicating that a box has taken damage.

    To solve these problems we use the convenient [HSV color
    model](http://en.wikipedia.org/wiki/HSL_and_HSV), which describes
    a cylindrical color space using three axes; Hue, Saturation and
    Value. This corresponds nicely with the three visual distinctions
    we need to make in the came.

    Each player gets a distinct hue (a base color like red, green,
    etc.)  equally spaced out in the hue color axis (from 0° to
    359°). Boxes belonging to a player use the same hue but a
    different, random saturation level within a reasonable interval
    (to avoid white boxes) and full value. When boxes take damage,
    they darken (i.e. get lower value) down to some minimum (to avoid
    black boxes). */
class Colored {
public:
  /// Constructs a color by copy constructing from the given color
  Colored(const QColor&);
  /// Returns a const referance to the color
  inline const QColor& color() { return color_; }
  /// Sets the color using copy assignment
  inline void setColor(const QColor& color) { color_ = color; }
protected:
  /// Returns any one hue randomly
  static int randomHue();
  /// Returns a random hue within a preset range
  static int randomSaturation();
  static const int kMinSaturation;
  static const int kMaxSaturation;
  /// The darkest value boxes can become when damaged
  static const int kMaxValue;
  /// The color value boxes start out with
  static const int kMinValue;
private:
  QColor color_;
};

#endif
