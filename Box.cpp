#include "Box.hpp"

#include <QBrush>

Box::Box(qreal x, qreal y, qreal width, qreal height) :
  // Interpret x and y arguments as the *top left corner of the box*,
  // not the center.
  QGraphicsRectItem{x - width / 2.0f, y - height / 2.0f, width, height},
  body{nullptr}
{
  setBrush(QBrush{Qt::white});
}

Box::~Box() {
  delete fixtureDef.shape;
  fixtureDef.shape = nullptr;
  // TODO: Delete body from world?
  //gameScene()->world()->DestroyBody(body);
  //body = nullptr;
}

void Box::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing

  if (phase == 0) return;

  if (body != nullptr and body->IsAwake())
    setPos(gameScene()->mapFromWorld(body->GetPosition()));
}

QVariant Box::itemChange(GraphicsItemChange change, const QVariant & value) {
  // TODO: Handle item being removed from scene
  if (change == QGraphicsItem::ItemSceneHasChanged) {
    b2PolygonShape* shape = new b2PolygonShape;
    b2Vec2 vec = gameScene()->mapToWorld(sceneBoundingRect().bottomRight());
    shape->SetAsBox(vec.x, vec.y);
    fixtureDef.density = 1;
    fixtureDef.restitution = 0.5f;
    fixtureDef.shape = shape;

    b2BodyDef bodyDef;
    bodyDef.userData = reinterpret_cast<void*>(this);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = gameScene()->mapToWorld(scenePos());
    body = gameScene()->world()->CreateBody(&bodyDef); // Copies content of bodyDef
    body->CreateFixture(&fixtureDef); // FIXME: Check that this doesn't leak memory
  }
  return value;
}
