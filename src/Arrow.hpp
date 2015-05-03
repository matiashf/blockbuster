#ifndef ARROW_HPP
#define ARROW_HPP

#include "Ball.hpp"

#include <QGraphicsItem>
#include <QTime>

/** Displays an impulse vector originating from a Ball.

    This is effectively the class that is used to control the
    ball. The arrow has a direction and both a desired and an
    available magnitude. A Player controls the Ball by rotating the
    arrow, changing its magnitude, and applying the resulting impulse
    vector to the Ball.

    When the impulse vector from the arrow is applied to the ball, the
    available magnitude decreases. Available magnitude is generated at
    at constant rate up to a maximum value.
 */
class Arrow : public QGraphicsItem {
private:
  QTime regeneration_; // For regenerating available magnitude
  qreal direction; // radians. horizontal right is zero, clockwise is positive.
  qreal desired_magnitude; // pixel impulses = pixels * kg / second
  qreal available_magnitude; // pixel impulses. Regenerates with time.
  qreal ball_radius; // pixels

  static const qreal kMagnitudeSteps;
  static const qreal kDirectionSteps;
  static const qreal kArrowLength;
  static const qreal kMaximumMagnitude;
  static const qreal kRegenerationTime;
  static const qreal kArrowAngle;
  static const qreal kTipLength;

  inline Ball* ball() { return dynamic_cast<Ball*>(parentItem()); }
public:
  Arrow(Ball* parent);

  /// Regenerates the available impulse
  void advance(int phase) override;

  /// Defines the drawing area in local coordinates
  virtual QRectF boundingRect() const;

  virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

  /// Rotates the arrow clockwise by the given radians.
  void increaseDirection(qreal radians);
  /// Increases the magnitude of the arrow up to a constant maximum.
  void increaseMagnitude(qreal difference);

  inline QTime* regeneration() { return &regeneration_; }

  /** Returns an impulse vector from the available/desired impulse.
      Decreases the available impulse. */
  QPointF getImpulseVector();

  inline void increase() { increaseMagnitude(kMaximumMagnitude / kMagnitudeSteps); }
  inline void decrease() { increaseMagnitude(-kMaximumMagnitude / kMagnitudeSteps); }
  inline void rotateLeft() { increaseDirection(-2.0d * M_PI / kDirectionSteps); }
  inline void rotateRight() { increaseDirection(2.0d * M_PI / kDirectionSteps); }
};

#endif
