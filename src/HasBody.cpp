#include "HasBody.hpp"

#include <QtMath> // qRadiansToDegrees
#include <stdexcept> // std::logic_error

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
  if (body_ != nullptr)
    throw new std::logic_error("A body has already been created.");
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

void HasBody::destroyBody() {
  if (body_ == nullptr)
    return;  // Not created yet or already destroyed
  gameScene()->world()->DestroyBody(body_);
  body_ = nullptr;
}

QVariant HasBody::itemChange(GraphicsItemChange change, const QVariant & value) {
  if (change == QGraphicsItem::ItemSceneChange)
    destroyBody();
  if (change == QGraphicsItem::ItemSceneHasChanged and scene() != nullptr)
    createBody();

  return QGraphicsItem::itemChange(change, value);
}
