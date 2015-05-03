#ifndef BOX_HPP
#define BOX_HPP

#include "PhysicalItem.hpp"
#include "Colored.hpp"

/** A physical, destructible box.

    Boxes have a base hue and a randomly chosen saturation. As they
    take damage, the color darkens.

    When a box has taken enough damage (its health reaches zero), it
    is removed from the scene and deleted.
*/
class Box : public PhysicalItem, public Colored, public Destructible {
private:
  QRectF rect_;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
  static const Destructible::Health kInitialHealth;
public:
  /// Constructs a Box with a random hue
  Box(qreal x, qreal y, qreal width, qreal height);
  /** Constructs a Box and places it on the scene. The x and y
      coordinates are scene coordinates referring to the top left
      corner of the box. */
  Box(qreal x, qreal y, qreal width, qreal height, int hue);

  /// Returns a rectangle for the box in local coordinates
  inline QRectF rect() const { return rect_; }
  /// Returns rect(). Used by QGraphicsScene.
  inline QRectF boundingRect() const { return rect(); }
  inline qreal width() { return rect().width(); };
  inline qreal height() { return rect().height(); };

  /// Changes color of the box when it takes damage
  void damage(Destructible::Health);
protected:
  void defineBody(b2BodyDef&);
  void defineFixture(b2FixtureDef&);
  b2Shape* createShape();
  /** Removes the box from the scene and deletes it. Called by
      Destructible::damage when health reaches zero. */
  void destroy();
};
#endif
