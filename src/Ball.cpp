#include "Ball.hpp"

#include <QBrush>

Ball::Ball(qreal x, qreal y, qreal radius) :
  QGraphicsEllipseItem{-radius, -radius, radius * 2, radius * 2},
  body{nullptr},
  impulseVector{0.0d, 0.0d}
{
  setBrush(QBrush{Qt::white});
  setPos(x + radius, y + radius);
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

void Ball::changeImpulseDirection(QPointF offset) {
  impulseVector += offset;
}

void Ball::applyImpulse() {
  bool wakeIfSleeping = true;
  body->ApplyLinearImpulse(gameScene()->mapToWorld(impulseVector),
                           body->GetPosition(), wakeIfSleeping);
}
