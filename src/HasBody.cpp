#include "HasBody.hpp"

#include <QtMath> // qRadiansToDegrees

HasBody::HasBody(qreal x, qreal y) :
  body_{nullptr}
{
  setPos(x, y);
}

HasBody::~HasBody() {
  // The body is owned by the Box2D world
}

void HasBody::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing

  if (phase == 0) return;

  if (body_ != nullptr and body_->IsAwake()) {
    setPos(gameScene()->mapFromWorld(body_->GetPosition()));
    setRotation(qRadiansToDegrees(body_->GetAngle()));
  }

  QGraphicsItem::advance(phase); // Advance children
}

void HasBody::createBody() {
  b2BodyDef bodyDef;
  defineBody(bodyDef);
  bodyDef.type = b2_dynamicBody;
  bodyDef.userData = reinterpret_cast<void*>(this); // For CollisionCallback
  bodyDef.position = gameScene()->mapToWorld(scenePos());
  this->body_ = gameScene()->world()->CreateBody(&bodyDef); // Copies content of bodyDef

  b2FixtureDef fixtureDef;
  defineFixture(fixtureDef);
  fixtureDef.shape = createShape();
  body_->CreateFixture(&fixtureDef); // Deep copies fixtureDef.
  delete fixtureDef.shape;
}

QVariant HasBody::itemChange(GraphicsItemChange change, const QVariant & value) {
  if (change == QGraphicsItem::ItemSceneHasChanged)
    createBody();
  return value;
}
