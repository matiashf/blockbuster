#include "Arrow.hpp"
#include "Ball.hpp"

#include <QtMath>
#include <QPainter>
#include <cmath> // M_PI
#include <QtMath> // qDegreesToRadians
#include <algorithm> // std::min

const qreal Arrow::kMaximumMagnitude = 1000.0d; // specific impulse (m/s)
const qreal Arrow::kMagnitudeSteps = 10.0d; // keypresses
const qreal Arrow::kDirectionSteps = 36.0d; // keypresses
const qreal Arrow::kArrowLength = 50.0d; // pixels
const qreal Arrow::kRegenerationTime = 3.0f; // seconds
const qreal Arrow::kArrowAngle = M_PI / 4.0f; // radians
const qreal Arrow::kTipLength = kArrowLength / 4.0d; // pixels

Arrow::Arrow(Ball* parent) :
  QGraphicsItem{parent},
  direction{-M_PI / 2.0}, // Straight up
  desired_magnitude{kMaximumMagnitude},
  available_magnitude{0},
  ball_radius{parent->radius()}
{
}

void Arrow::advance(int phase) {
  // phase 0: The scene is about to advance
  // phase 1: The scene is advancing
  if (phase == 0) return;

  if (available_magnitude >= kMaximumMagnitude) {
    regeneration_.restart(); // Clear the timer
    return; // Fully regenerated already
  }

  // Regenerate up to maximum
  const qreal rate = kMaximumMagnitude / kRegenerationTime;
  const qreal seconds = regeneration_.restart() / 1000.0f; // msec timer
  available_magnitude += rate * seconds;
  if (available_magnitude > kMaximumMagnitude)
    available_magnitude = kMaximumMagnitude;
  update(); // Schedule redraw
}

QRectF Arrow::boundingRect() const {
  qreal x = qCos(direction) * desired_magnitude;
  qreal y = qSin(direction) * desired_magnitude;
  return QRectF{0, 0, x, y}.normalized();
}

void Arrow::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  if (desired_magnitude == 0)
    return;

  // Unit vectors
  qreal direction = this->direction - qDegreesToRadians(ball()->rotation());
  qreal x = qCos(direction), y = qSin(direction);

  const qreal scale = kArrowLength / kMaximumMagnitude;

  // Lengths
  qreal available_length = ball_radius + std::min(available_magnitude, desired_magnitude) * scale;
  qreal desired_length = ball_radius + desired_magnitude * scale;

  // Points
  QPointF edge_of_ball{x * ball_radius, y * ball_radius};
  QPointF end_of_available_line{x * available_length, y * available_length};
  QPointF arrow_tip{x * desired_length, y * desired_length};

  // Draw
  QPen pen;
  pen.setWidth(4); // Pixels
  // Green line
  pen.setColor(Qt::green);
  painter->setPen(pen); // Pass by value
  painter->drawLine(QLineF{edge_of_ball, end_of_available_line});
  // Red line
  if (available_length < desired_length) {
    pen.setColor(Qt::red);
    painter->setPen(pen); // Pass by value
    painter->drawLine(QLineF{end_of_available_line, arrow_tip});
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

QPointF Arrow::getImpulseVector() {
  qreal direction = qDegreesToRadians(rotation()) + this->direction;
  qreal magnitude = std::min(available_magnitude, desired_magnitude);
  available_magnitude -= magnitude;
  magnitude *= ball()->body()->GetMass(); // calculate impulse from specific impulse
  qreal x = qCos(direction) * magnitude;
  qreal y = qSin(direction) * magnitude;
  return QPointF{x, y};
}

void Arrow::increaseDirection(qreal radians) {
  prepareGeometryChange(); // Let the scene know that the object changes size

  direction += radians;

  // normalize to be within the interval [0, tau)
  qreal tau = 2 * M_PI;
  while (direction >= tau)
    direction -= tau;
  while (direction < 0)
    direction += tau;
}

void Arrow::increaseMagnitude(qreal difference) {
  prepareGeometryChange(); // Let the scene know that the object changes size
  desired_magnitude += difference;
  if (desired_magnitude < 0)
    desired_magnitude = 0;
  if (desired_magnitude > kMaximumMagnitude)
    desired_magnitude = kMaximumMagnitude;
}
