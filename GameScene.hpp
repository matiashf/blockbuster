#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <QtWidgets/QGraphicsScene>
#include <QTimer>
#include <QTime>

#include <Box2D.h>

class GameScene: public QGraphicsScene {
  Q_OBJECT
private:
  QTimer* timer; // Periodic event dispatcher
  QTime timeAccumulator; // Clock

  /* Use a constraint-based physics engine, like this:
     http://allenchou.net/2013/12/game-physics-constraints-sequential-impulse */
  b2Vec2 gravity;
  b2World world_;

  /* The constants below are given as arguments to the box2d world step
     function, and set the maximum number of iterations allowed during
     numerical approximations for velocity and position. Essentially,
     the higher the number the more accurate simulation of
     collitions. Setting the value too high, however, will cause the
     simulation to slow down *in some corner cases*.

     See http://www.iforce2d.net/b2dtut/worlds for a more detailed
     description.*/
  static const int kMaxVelocityIterations;
  static const int kMaxPositionIterations;

public:
  GameScene(QObject* parent=0);

  inline b2World* world() { return &world_; }
public slots:
  void advance();
};

#endif
