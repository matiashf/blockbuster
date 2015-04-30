#ifndef BALL_HPP
#define BALL_HPP

#include "HasBody.hpp"
#include "HasColor.hpp"

class Arrow;

class Ball : public HasBody, public HasColor {
private:
  qreal radius_;
  Arrow* arrow_;
public:
  Ball(qreal x, qreal y, qreal radius, int hue);
  Ball(qreal x, qreal y, qreal radius);
  inline qreal radius() const { return radius_; }
  inline QRectF boundingRect() const {
    return QRectF{-radius(), -radius(), radius() * 2.0f, radius() * 2.0f};
  }
  inline Arrow* arrow() { return arrow_; }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
protected:
  void defineBody(b2BodyDef&);
  void defineFixture(b2FixtureDef&);
  b2Shape* createShape();
public slots:
  void applyImpulse();
};
#endif
