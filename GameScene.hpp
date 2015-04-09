#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <QtWidgets/QGraphicsScene>
#include <btBulletDynamicsCommon.h>

class GameScene: public QGraphicsScene {
  Q_OBJECT
private:
  QTimer* timer;

  /* Bullet is a constraint-based physics engine, like this:
     http://allenchou.net/2013/12/game-physics-constraints-sequential-impulse
  */
  btDefaultCollisionConfiguration configuration;
  btCollisionDispatcher dispatcher; // Determines collision details?
  btDbvtBroadphase broadphase; // Fast, coarse collision detection
  btSequentialImpulseConstraintSolver solver; // Deals with forces and momentum?
  btDiscreteDynamicsWorld world; // A world of non-deformable collision objects

public:
  GameScene(QObject* parent=0);
public slots:
  void advance();
};

#endif
