#ifndef BOX_HPP
#define BOX_HPP

#include <QGraphicsRectItem>

class Box : public QGraphicsRectItem {
public:
  Box(qreal x, qreal y, qreal width, qreal height);
protected slots:
  void advance(int phase) override;
};

#endif
