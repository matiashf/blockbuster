#ifndef BALL_HPP
#define BALL_HPP

#include <QGraphicsEllipseItem>
#include <Box2D.h>

#include "GameScene.hpp"

class ImpulseVectorItem; // Forward declaration

class Ball : public QGraphicsEllipseItem {
private:
  b2Body* body;
  ImpulseVectorItem* impulseVector_;
  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}
public:
  Ball(qreal x, qreal y, qreal radius);
  inline qreal radius() { return rect().width() / 2.0d; }
  inline ImpulseVectorItem* impulseVector() { return impulseVector_; }
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
public slots:
  void applyImpulse();
};

#endif
