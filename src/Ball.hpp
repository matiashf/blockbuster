#ifndef BALL_HPP
#define BALL_HPP

#include <QGraphicsEllipseItem>
#include <Box2D.h>

#include "Arrow.hpp"
#include "GameScene.hpp"

class Ball : public QGraphicsEllipseItem {
private:
  static const int kNoHueSpecified;

  b2Body* body;
  Arrow* arrow_;
  QColor color; // Used to store hue
  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}
public:
  static int randomHue();
  Ball(qreal x, qreal y, qreal radius, int hue=kNoHueSpecified);
  inline qreal radius() { return rect().width() / 2.0d; }
  inline Arrow* arrow() { return arrow_; }
  inline int hue() const { return color.hue(); }
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
public slots:
  void applyImpulse();
};

#endif
