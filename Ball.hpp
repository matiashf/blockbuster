#ifndef BALL_HPP
#define BALL_HPP

#include <QGraphicsEllipseItem>

class Ball : public QGraphicsEllipseItem {
public:
  Ball();
  void advance(int phase) override;
};

#endif
