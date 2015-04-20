#ifndef BOX_HPP
#define BOX_HPP

#include "GameScene.hpp"

#include <QGraphicsRectItem>
#include <QVariant>
#include <Box2D.h>


// More on what frames of reference are used in QGraphicsScene and Box2D:
// * http://stackoverflow.com/a/1151955/2719221
// * http://gamedev.stackexchange.com/a/3760

class Box : public QGraphicsRectItem {
private:
  b2FixtureDef fixtureDef;
  b2Body* body;

  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}
public:
  Box(qreal x, qreal y, qreal width, qreal height);
  ~Box();
  inline qreal width() { return rect().x() * 2.0d; };
  inline qreal height() { return rect().y() * 2.0d; };
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};

#endif
