#include "Ball.hpp"

#include <QBrush>

Ball::Ball() :
  QGraphicsEllipseItem{0, 0, 50, 50}
{
  setBrush(QBrush{Qt::black});
}
