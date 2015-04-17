#include "Box.hpp"

#include <QBrush>

Box::Box(qreal x, qreal y, qreal width, qreal height) :
  // Interpret x and y arguments as the *top left corner of the box*,
  // not the center.
  QGraphicsRectItem{x - width / 2.0f, y - height / 2.0f, width, height},
{
  setBrush(QBrush{Qt::white});
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
