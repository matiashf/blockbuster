#ifndef BOX_HPP
#define BOX_HPP

#include "GameScene.hpp"
#include "HasColor.hpp"

#include <QGraphicsRectItem>
#include <QVariant>
#include <Box2D.h>

// More on what frames of reference are used in QGraphicsScene and Box2D:
// * http://stackoverflow.com/a/1151955/2719221
// * http://gamedev.stackexchange.com/a/3760

class Box : public QGraphicsItem, public HasColor {
private:
  QRectF rect_;

  b2Body* body;

  inline GameScene* gameScene() {return dynamic_cast<GameScene*>(scene());}
  inline qreal radiansToDegrees(qreal radians) { return radians * 180.0d / M_PI; }

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
public:
  Box(qreal x, qreal y, qreal width, qreal height);
  Box(qreal x, qreal y, qreal width, qreal height, int hue);

  inline QRectF rect() const { return rect_; }
  inline QRectF boundingRect() const { return rect(); }
  inline qreal width() { return rect().width(); };
  inline qreal height() { return rect().height(); };
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};
#endif
