#ifndef ARROW_HPP
#define ARROW_HPP

#include <QGraphicsItem>
#include <QTime>

class Ball; // Forward declaration

class Arrow : public QGraphicsItem {
private:
  QTime time; // For regenerating available magnitude
  qreal direction; // radians. horizontal right is zero, clockwise is positive.
  qreal desired_magnitude; // pixel impulses = pixels * kg / second
  qreal available_magnitude; // pixel impulses. Regenerates with time.
  qreal ball_radius; // pixels

  static const qreal kMagnitudeSteps;
  static const qreal kDirectionSteps;
  static const qreal kArrowLength;
  static const qreal kMaximumMagnitude;
  static const qreal kRegenerationTime;
  static const qreal kArrowAngle;
  static const qreal kTipLength;
public:
  Arrow(Ball* parent);

  void advance(int phase) override;

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

  void increaseDirection(qreal radians);
  void increaseMagnitude(qreal difference);

  QPointF getImpulseVector();

  inline void increase() { increaseMagnitude(kMaximumMagnitude / kMagnitudeSteps); }
  inline void decrease() { increaseMagnitude(-kMaximumMagnitude / kMagnitudeSteps); }
  inline void rotateLeft() { increaseDirection(-2.0d * M_PI / kDirectionSteps); }
  inline void rotateRight() { increaseDirection(2.0d * M_PI / kDirectionSteps); }
};

#endif
