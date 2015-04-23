#include "ImpulseVectorItem.hpp"
#include "Ball.hpp"

#include <QtMath>
#include <QPainter>
#include <cmath> // M_PI
#include <algorithm> // std::min

const qreal ImpulseVectorItem::kMaximumMagnitude = 2000.0d; // pixel impulses
const qreal ImpulseVectorItem::kMagnitudeSteps = 10.0d; // keypresses
const qreal ImpulseVectorItem::kDirectionSteps = 36.0d; // keypresses
const qreal ImpulseVectorItem::kArrowLength = 50.0d; // pixels
const qreal ImpulseVectorItem::kRegenerationTime = 5.0f; // seconds
const qreal ImpulseVectorItem::kArrowAngle = M_PI / 4.0f; // radians
const qreal ImpulseVectorItem::kTipLength = kArrowLength / 4.0d; // pixels

ImpulseVectorItem::ImpulseVectorItem(Ball* parent) :
  QGraphicsItem{parent},
  direction{0},
  desired_magnitude{0},
  actual_magnitude{kMaximumMagnitude},
  ball_radius{parent->radius()}
{
  time.start();
}

void ImpulseVectorItem::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing
  if (phase == 0) return;

  // Regenerate up to maximum
  const qreal rate = kMaximumMagnitude / kRegenerationTime;
  const qreal seconds = time.restart() / 1000.0f; // msec timer
  actual_magnitude += rate * seconds;
  if (actual_magnitude > kMaximumMagnitude)
    actual_magnitude = kMaximumMagnitude;
}

QRectF ImpulseVectorItem::boundingRect() const {
  qreal x = qCos(direction) * desired_magnitude;
  qreal y = qSin(direction) * desired_magnitude;
  return QRectF{0, 0, x, y}.normalized();
}

void ImpulseVectorItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  if (desired_magnitude == 0)
    return;

  // Unit vectors
  qreal x = qCos(direction), y = qSin(direction);

  const qreal scale = kArrowLength / kMaximumMagnitude;

  // Lengths
  qreal actual_length = ball_radius + std::min(actual_magnitude, desired_magnitude) * scale;
  qreal desired_length = ball_radius + desired_magnitude * scale;

  // Points
  QPointF edge_of_ball{x * ball_radius, y * ball_radius};
  QPointF end_of_actual_line{x * actual_length, y * actual_length};
  QPointF arrow_tip{x * desired_length, y * desired_length};

  // Draw
  QPen pen;
  pen.setWidth(4); // Pixels
  // Green line
  pen.setColor(Qt::green);
  painter->setPen(pen); // Pass by value
  painter->drawLine(QLineF{edge_of_ball, end_of_actual_line});
  // Red line
  if (actual_length < desired_length) {
    pen.setColor(Qt::red);
    painter->setPen(pen); // Pass by value
    painter->drawLine(QLineF{end_of_actual_line, arrow_tip});
  }
  // Arrow head
  qreal head_distance = qSqrt(
    pow(kTipLength, 2.0d) + pow(desired_length, 2.0d)
    - 2 * kTipLength * desired_length * qCos(kArrowAngle));
  qreal head_angle = qAsin(kTipLength / head_distance * qSin(kArrowAngle));
  for (qreal sign = -1; sign <= 1; sign += 2) {
    qreal angle = direction + sign * head_angle;
    painter->drawLine(arrow_tip, QPointF{qCos(angle) * head_distance,
                                         qSin(angle) * head_distance});
  }
}

QPointF ImpulseVectorItem::getActual() {
  qreal magnitude = std::min(actual_magnitude, desired_magnitude);
  actual_magnitude -= magnitude;
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
  desired_magnitude += difference;
  if (desired_magnitude < 0)
    desired_magnitude = 0;
  if (desired_magnitude > kMaximumMagnitude)
    desired_magnitude = kMaximumMagnitude;
}
