#ifndef BOX_HPP
#define BOX_HPP

#include "HasBody.hpp"
#include "HasColor.hpp"

class Box : public HasBody, public HasColor {
private:
  QRectF rect_;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
public:
  Box(qreal x, qreal y, qreal width, qreal height);
  Box(qreal x, qreal y, qreal width, qreal height, int hue);

  inline QRectF rect() const { return rect_; }
  inline QRectF boundingRect() const { return rect(); }
  inline qreal width() { return rect().width(); };
  inline qreal height() { return rect().height(); };
protected:
  void defineBody(b2BodyDef&);
  void defineFixture(b2FixtureDef&);
  b2Shape* createShape();
};
#endif
