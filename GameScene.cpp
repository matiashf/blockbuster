#include "GameScene.hpp"
#include "Ball.hpp"

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, 1920, 1080, parent}, // x, y, width, height. Full HD.
  timer{new QTimer{this}},
  dispatcher{&configuration},
  world{&dispatcher, &broadphase, &solver, &configuration}
{
  world.setGravity(btVector3{0, -9.81, 0}); // Earth gravity
  timeAccumulator.start(); // For synchronizing the physics engine with real time

  connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
  /* If advance() exceeds its designated time slice, QTimer will skip
     timeout()-events. Effectively this gives variable frame rate by
     simply dropping frames. */
  timer->start(1000.0 / 60.0); // 60 FPS => ~16 msec time period

  addItem(new Ball{width() / 2, height() / 2, 5});
}

void GameScene::advance() {
  world.stepSimulation(timeAccumulator.restart());

  QGraphicsScene::advance(); // Advance items, i.e. render
}
