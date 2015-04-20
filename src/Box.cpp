#include "Box.hpp"

#include <QBrush>

Box::Box(qreal x, qreal y, qreal width, qreal height) :
  // The (x, y)-coordinates given to the parent constructor below
  // specify where the center of the box is drawn relative to the box
  // reference system. Essentially, this makes it so that when we talk
  // about where the box is positioned in scene coordinates, we mean
  // specifically the center of the box.
  QGraphicsRectItem{width / 2.0f, height / 2.0f, width, height},
  body{nullptr}
{
  setBrush(QBrush{Qt::white});
  // Position the top left corner of the box at scene coordinates (x, y)
  setPos(x + width / 2.0f, y + height / 2.0f);
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
