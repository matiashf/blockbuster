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
  b2Body* body;

  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}
  inline qreal radiansToDegrees(qreal radians) { return radians * 180.0d / M_PI; }
public:
  Box(qreal x, qreal y, qreal width, qreal height);
  inline qreal width() { return rect().width(); };
  inline qreal height() { return rect().height(); };
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};

#endif
