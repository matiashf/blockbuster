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
  QTime worldTime; // Clock for synchronizing the physics world with real time

  /* Use a constraint-based physics engine, like this:
     http://allenchou.net/2013/12/game-physics-constraints-sequential-impulse */
  b2Vec2 gravity;
  b2World world_;
  const qreal worldScale; // in world meters per scene pixel

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

  // For calculating worldScale, we set the number of seconds it takes
  // an object to free fall from the top to the bottom of the screen.
  static const float kScaleFactor;

  // The number of times per seconds advance() should be called
  static const qreal kFrameRate;
public:
  GameScene(QObject* parent=0);

  inline b2World* world() { return &world_; }

  // Convenience functions for mapping between world and scene coordinates
  inline float32 mapToWorld(qreal scalar) { return scalar * worldScale; }
  inline qreal mapFromWorld(float32 scalar) { return scalar / worldScale; }
  inline b2Vec2 mapToWorld(const QPointF & vector) {
    return b2Vec2{mapToWorld(vector.x()), mapToWorld(vector.y())};
  }
  inline QPointF mapFromWorld(const b2Vec2 & vector) {
    return QPointF{mapFromWorld(vector.x), mapFromWorld(vector.y)};
  }
  inline b2Vec2 mapToWorld(qreal x, qreal y) {
    return b2Vec2{mapToWorld(x), mapToWorld(y)};
  }

public slots:
  void start();
  void stop();
  void toggle();
  void advance(qreal milliseconds);
  void advance();
};

#endif