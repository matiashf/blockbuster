#ifndef BALL_HPP
#define BALL_HPP

#include <QGraphicsEllipseItem>
#include <Box2D.h>

class Ball : public QGraphicsEllipseItem {
private:
  b2Body* body;
  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}
public:
  Ball(qreal x, qreal y, qreal radius);
  inline qreal radius() { return rect().width() / 2.0d; };
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};

#endif
