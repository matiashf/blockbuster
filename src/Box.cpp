#include "Box.hpp"

#include <cmath> // M_PI
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
  QColor color{float(rand() % 255), float(rand() % 255), float(rand() % 255)};
  setBrush(QBrush{color});
  setPen(QPen{color});
  // Determine where the box origin is situated relative to the scene origin
  setPos(x + width / 2, y + height / 2);
}

void Box::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing

  if (phase == 0) return;

  if (body != nullptr and body->IsAwake()) {
    setPos(gameScene()->mapFromWorld(body->GetPosition()));
    setRotation(radiansToDegrees(body->GetAngle()));
  }
}

QVariant Box::itemChange(GraphicsItemChange change, const QVariant & value) {
  // TODO: Handle item being removed from scene
  if (change == QGraphicsItem::ItemSceneHasChanged) {
    // Create a Box2D body using a temporary body definition
    b2BodyDef bodyDef;
    bodyDef.userData = reinterpret_cast<void*>(this); // For collision callbacks
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = gameScene()->mapToWorld(scenePos());
    body = gameScene()->world()->CreateBody(&bodyDef); // Copies content of bodyDef

    // Attach a fixture (with a shape) to the body using a temporary
    // fixture definition.
    b2PolygonShape shape;
    shape.SetAsBox(gameScene()->mapToWorld(width() / 2.0d),
                   gameScene()->mapToWorld(height() / 2.0d));
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.1f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef); // Deep copies fixtureDef.

    // The shape is owned by the fixture, the fixture is owned by the
    // body, the body is owned by the world, and the world is owned by
    // the scene. No further memory management is required in this
    // class.
  }
  return value;
}
