#ifndef BOX_HPP
#define BOX_HPP

#include <QGraphicsRectItem>
#include <QVariant>

class Box : public QGraphicsRectItem {
public:
  Box(qreal x, qreal y, qreal width, qreal height);
protected slots:
  void advance(int phase) override;
  QVariant itemChange(GraphicsItemChange change, const QVariant & value);
};

#endif
