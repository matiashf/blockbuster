#ifndef IMPULSE_VECTOR_ITEM_HPP
#define IMPULSE_VECTOR_ITEM_HPP

#include <QGraphicsItem>
#include <QTime>

class Ball; // Forward declaration

class ImpulseVectorItem : public QGraphicsItem {
private:
  QTime time; // For regenerating actual magnitude
  qreal direction; // radians. horizontal right is zero, clockwise is positive.
  qreal desired_magnitude; // pixel impulses = pixels * kg / second
  qreal actual_magnitude; // pixel impulses. Regenerates with time.
  qreal ball_radius; // pixels

  static const qreal kMagnitudeSteps;
  static const qreal kDirectionSteps;
  static const qreal kArrowLength;
  static const qreal kMaximumMagnitude;
  static const qreal kRegenerationTime;
  static const qreal kArrowAngle;
  static const qreal kTipLength;
public:
  ImpulseVectorItem(Ball* parent);

  void advance(int phase) override;

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

  void increaseDirection(qreal radians);
  void increaseMagnitude(qreal difference);

  QPointF getActual();

  inline void increase() { increaseMagnitude(kMaximumMagnitude / kMagnitudeSteps); }
  inline void decrease() { increaseMagnitude(-kMaximumMagnitude / kMagnitudeSteps); }
  inline void rotateLeft() { increaseDirection(-2.0d * M_PI / kDirectionSteps); }
  inline void rotateRight() { increaseDirection(2.0d * M_PI / kDirectionSteps); }
};

#endif
