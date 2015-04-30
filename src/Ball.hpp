#ifndef BALL_HPP
#define BALL_HPP

#include "HasColor.hpp"

#include <QGraphicsEllipseItem>
#include <Box2D.h>

#include "Arrow.hpp"
#include "GameScene.hpp"

class Ball : public QGraphicsItem, public HasColor {
private:
  qreal radius_;
  b2Body* body;
  Arrow* arrow_;
  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}
public:
  Ball(qreal x, qreal y, qreal radius, int hue);
  Ball(qreal x, qreal y, qreal radius);
  inline qreal radius() const { return radius_; }
  inline QRectF boundingRect() const {
    return QRectF{-radius(), -radius(), radius() * 2.0f, radius() * 2.0f};
  }
  inline Arrow* arrow() { return arrow_; }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
public slots:
  void applyImpulse();
};
#endif
