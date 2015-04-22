#include "Ball.hpp"

#include <QBrush>

Ball::Ball(qreal x, qreal y, qreal radius) :
  QGraphicsEllipseItem{-radius, -radius, radius * 2, radius * 2},
{
  setBrush(QBrush{Qt::white});
  setPos(x + radius, y + radius);
}

void Ball::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing

  if (phase == 0) return;

  moveBy(1, 1);
}
