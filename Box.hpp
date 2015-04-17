#ifndef BOX_HPP
#define BOX_HPP

#include "GameScene.hpp"

#include <QGraphicsRectItem>
#include <QVariant>
#include <Box2D.h>

class Box : public QGraphicsRectItem {
private:
  b2FixtureDef fixtureDef;
  b2Body* body;

  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}
public:
  Box(qreal x, qreal y, qreal width, qreal height);
  ~Box();
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};

#endif
