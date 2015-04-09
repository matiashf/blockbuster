#include "Ball.hpp"

#include <QBrush>

Ball::Ball() :
  QGraphicsEllipseItem{0, 0, 50, 50}
{
  setBrush(QBrush{Qt::black});
}

void Ball::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing

  if (phase == 0) return;

  moveBy(1, 1);
}