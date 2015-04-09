#ifndef BALL_HPP
#define BALL_HPP

#include <QGraphicsEllipseItem>

class Ball : public QGraphicsEllipseItem {
public:
  Ball(qreal x, qreal y, qreal radius);
protected slots:
  void advance(int phase) override;
};

#endif
