#include "Box.hpp"

#include <QPainter>

Box::Box(qreal x, qreal y, qreal width, qreal height) :
  Box{x, y, width, height, randomHue()}
{
}

Box::Box(qreal x, qreal y, qreal width, qreal height, int hue) :
  // The (x, y) scene coordinates above specify where the top left
  // corner of the box is drawn. This is helpful for when we create
  // boxes on the scene based on a grid in a text file.

  // However, to simplify integration with Box2D (which might revolve
  // rotation around the center of mass), we specify that the box
  // reference system originate in the center of the box. Since the
  // box has uniform weight distribution, this is also the center of
  // mass.

  // Determine where the box origin is situated relative to the scene origin
  HasBody{x + width / 2, y + height / 2},
  HasColor{QColor::fromHsv(hue, randomSaturation(), kMaxValue)},
  // Determine where the box is drawn relative to its local origin
  rect_{-width / 2.0d, -height / 2.0d, width, height}
{
}

void Box::defineBody(b2BodyDef& def) {
  def.angularDamping = 1.0f; // Increase the angular inertia (i.e. spin less)
}

void Box::defineFixture(b2FixtureDef& def) {
  def.density = 1.0f;
  def.restitution = 0.1f;
}

b2Shape* Box::createShape() {
  b2PolygonShape* shape = new b2PolygonShape;
  shape->SetAsBox(gameScene()->mapToWorld(width() / 2.0d),
                  gameScene()->mapToWorld(height() / 2.0d));
  return shape;
}

void Box::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->setBrush(QBrush{color()});
  painter->setPen(QPen{color()});
  painter->drawRect(rect());
}
