#include "Ball.hpp"
#include "Arrow.hpp"
#include "GameScene.hpp"

#include <stdexcept> // std::range_error
#include <QPainter>

Ball::Ball(qreal x, qreal y, qreal radius) :
  Ball{x, y, radius, randomHue()}
{
}

Ball::Ball(qreal x, qreal y, qreal radius, int hue) :
  HasBody{x + radius, y + radius},
  HasColor{QColor::fromHsv(hue, kMaxSaturation, kMaxValue)},
  radius_{radius},
  arrow_{new Arrow{this}}
{
  setZValue(1); // Draw in front of boxes (which have default Z-value of 0)
}

void Ball::defineBody(b2BodyDef& def) {
  // Prevent the ball from ever passing through another object, at the
  // cost of more expensive collision calculations.
  def.bullet = true; 
}

void Ball::defineFixture(b2FixtureDef& def) {
  def.density = 1.0f;
  def.restitution = 0.5f;
}

b2Shape* Ball::createShape() {
  b2CircleShape* shape = new b2CircleShape;
  shape->m_p.Set(0, 0); // Draw the center of the circle at the body origin
  shape->m_radius = gameScene()->mapToWorld(radius());
  return shape;
}

void Ball::applyImpulse() {
  QPointF impulse = arrow()->getImpulseVector();
  bool wakeIfSleeping = true;
  body()->ApplyLinearImpulse(gameScene()->mapToWorld(impulse),
                             body()->GetPosition(), wakeIfSleeping);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->setBrush(QBrush{color()});
  painter->setPen(QPen{color()});
  painter->drawEllipse(boundingRect());
}
