#include "Ball.hpp"
#include "Arrow.hpp"

#include <stdexcept> // std::range_error
#include <QPainter>
#include <QColor>

const int Ball::kNoHueSpecified = -1;

int Ball::randomHue() {
  return rand() % 360; // TODO: Use the new C++ 11 random module
}

Ball::Ball(qreal x, qreal y, qreal radius, int hue) :
  radius_{radius},
  body{nullptr},
  arrow_{new Arrow{this}},
  // maximum saturation and value is 255, see the color section in DESIGN.md
  color{QColor::fromHsv((hue == kNoHueSpecified) ? randomHue() : hue, 255, 255)}
{
  if (!color.isValid())
    throw std::range_error("Hue is outside of valid range");

  setPos(x + radius, y + radius);
  setZValue(1); // Draw in front of boxes (which have default Z-value of 0)
}

void Ball::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing

  if (phase == 0) return;

  if (body != nullptr and body->IsAwake()) {
    setPos(gameScene()->mapFromWorld(body->GetPosition()));
    // TODO: Apply rotation
  }
}

QVariant Ball::itemChange(GraphicsItemChange change, const QVariant & value) {
  if (change == QGraphicsItem::ItemSceneHasChanged) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true; // Prevent the ball from ever passing through another object, at the cost of more expensive collision calculations.
    bodyDef.position = gameScene()->mapToWorld(scenePos());
    body = gameScene()->world()->CreateBody(&bodyDef); // Copies content of bodyDef

    b2CircleShape shape;
    shape.m_p.Set(0, 0); // Draw the center of the circle at the body origin
    shape.m_radius = gameScene()->mapToWorld(radius());
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.5f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef); // Deep copies fixtureDef.
  }
  return value;
}

void Ball::applyImpulse() {
  QPointF impulse = arrow()->getImpulseVector();
  bool wakeIfSleeping = true;
  body->ApplyLinearImpulse(gameScene()->mapToWorld(impulse),
                           body->GetPosition(), wakeIfSleeping);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->setBrush(QBrush{color});
  painter->setPen(QPen{color});
  painter->drawEllipse(boundingRect());
}
