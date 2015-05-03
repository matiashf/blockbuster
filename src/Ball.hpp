#ifndef BALL_HPP
#define BALL_HPP

#include "PhysicalItem.hpp"
#include "HasColor.hpp"

class Arrow;

/** A Player controlled physical object used to break boxes.

    When constructing the Ball, an Arrow is also created that moves
    with the ball. It is a child of the ball in the QGraphicsItem
    hierarchy.

    The ball is indestructible.
 */
class Ball : public PhysicalItem, public HasColor {
private:
  qreal radius_;
  Arrow* arrow_;
public:
  /** Construct a new ball and positions it on the scene. The x and y
      coordinates are scene coordinates, and the ball is placed so
      that the top left corner of its containing rectangle is at the
      given x and y position. */
  Ball(qreal x, qreal y, qreal radius, int hue);
  /// Constructs a ball with a random hue
  Ball(qreal x, qreal y, qreal radius);
  /// Returns the radius (in pixels) of the ball
  inline qreal radius() const { return radius_; }
  /// Returns the containing rectangle of the ball in local coordinates
  inline QRectF boundingRect() const {
    return QRectF{-radius(), -radius(), radius() * 2.0f, radius() * 2.0f};
  }
  /// Returns the arrow used to control the ball
  inline Arrow* arrow() { return arrow_; }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
protected:
  void defineBody(b2BodyDef&);
  void defineFixture(b2FixtureDef&);
  b2Shape* createShape();
public slots:
  void applyImpulse();
};
#endif
