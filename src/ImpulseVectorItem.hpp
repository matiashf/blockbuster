#ifndef IMPULSE_VECTOR_ITEM_HPP
#define IMPULSE_VECTOR_ITEM_HPP

#include <QGraphicsItem>

class Ball; // Forward declaration

class ImpulseVectorItem : public QGraphicsItem {
private:
  qreal direction; // in radians. zero is right, clockwise is positive.
  qreal magnitude; // in pixels * kg / second
  qreal ball_radius;

  static const qreal kMagnitudeStep;
  static const qreal kDirectionStep;
public:
  ImpulseVectorItem(Ball* parent);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

  void increaseDirection(qreal radians);
  void increaseMagnitude(qreal difference);

  QPointF getVector() const;
  inline void increase() { increaseMagnitude(kMagnitudeStep); }
  inline void decrease() { increaseMagnitude(-kMagnitudeStep); }
  inline void rotateLeft() { increaseDirection(-kDirectionStep); }
  inline void rotateRight() { increaseDirection(kDirectionStep); }
};

#endif
