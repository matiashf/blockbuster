#include "ImpulseVectorItem.hpp"
#include "Ball.hpp"

#include <QtMath>
#include <QPainter>
#include <cmath> // M_PI

const qreal ImpulseVectorItem::kMagnitudeStep = 100.0d; // impulses per keypress
const qreal ImpulseVectorItem::kDirectionStep = M_PI / 18.0d; // radians per keypress
const qreal ImpulseVectorItem::kScaleFactor =
  1.0f / ImpulseVectorItem::kMagnitudeStep; // pixels per impulse

ImpulseVectorItem::ImpulseVectorItem(Ball* parent) :
  QGraphicsItem{parent},
  direction{0},
  magnitude{0},
  ball_radius{parent->radius()}
{
}

QRectF ImpulseVectorItem::boundingRect() const {
  return QRectF{QPointF{0, 0}, getVector()}.normalized();
}

void ImpulseVectorItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  QPen pen;
  pen.setWidth(4); // Pixels
  pen.setColor(Qt::red);
  painter->setPen(pen); // Pass by reference

  // Determine positions to paint
  qreal x = qCos(direction), y = qSin(direction); // Unit vectors

  qreal scaled_magnitude = ball_radius + magnitude * kScaleFactor;

  QPointF edge_of_ball{x * ball_radius, y * ball_radius};
  QPointF tip_of_vector{x * scaled_magnitude, y * scaled_magnitude};

  painter->drawLine(QLineF{edge_of_ball, tip_of_vector});
}

QPointF ImpulseVectorItem::getVector() const {
  qreal x = qCos(direction) * magnitude;
  qreal y = qSin(direction) * magnitude;
  return QPointF{x, y};
}

void ImpulseVectorItem::increaseDirection(qreal radians) {
  prepareGeometryChange(); // Let the scene know that the object changes size

  direction += radians;

  // normalize to be within the interval [0, tau)
  qreal tau = 2 * M_PI;
  while (direction >= tau)
    direction -= tau;
  while (direction < 0)
    direction += tau;
}

void ImpulseVectorItem::increaseMagnitude(qreal difference) {
  prepareGeometryChange(); // Let the scene know that the object changes size
  magnitude += difference;
  if (magnitude < 0)
    magnitude = 0;
}
