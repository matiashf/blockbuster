#include "Box.hpp"

#include <QBrush>

Box::Box(qreal x, qreal y, qreal width, qreal height) :
  QGraphicsRectItem{x, y, width, height}
{
  setBrush(QBrush{Qt::black});
}

void Box::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing

  if (phase == 0) return;

  // FIXME: Obtain position from physics world
}

QVariant Box::itemChange(GraphicsItemChange change, const QVariant & value) {
  // TODO: Handle item being removed from scene
  if (change == QGraphicsItem::ItemSceneHasChanged) {
    // FIXME: Add to new scene world
  }
  return value;
}
