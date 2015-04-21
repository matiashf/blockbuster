#include "Box.hpp"

#include <QBrush>

Box::Box(qreal x, qreal y, qreal width, qreal height) :
  // The (x, y) scene coordinates above specify where the top left
  // corner of the box is drawn. This is helpful for when we create
  // boxes on the scene based on a grid in a text file.

  // However, to simplify integration with Box2D (which might revolve
  // rotation around the center of mass), we specify that the box
  // reference system originate in the center of the box. Since the
  // box has uniform weight distribution, this is also the center of
  // mass.

  // Determine where the box is drawn relative to its origin
  QGraphicsRectItem{-width / 2.0d, -height / 2.0d, width, height},
  body{nullptr}
{
  setBrush(QBrush{Qt::white});
  // Determine where the box origin is situated relative to the scene origin
  setPos(x + width / 2, y + height / 2);
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
    shape->SetAsBox(gameScene()->mapToWorld(width()),
                    gameScene()->mapToWorld(height()));
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
