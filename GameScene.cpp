#include "GameScene.hpp"
#include "Ball.hpp"

#include <QTimer>

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, 1920, 1080, parent}, // x, y, width, height. Full HD.
  timer{new QTimer{this}},
  dispatcher{&configuration},
  world{&dispatcher, &broadphase, &solver, &configuration}
{
  timer->start(1000.0 / 60.0); // 60 FPS => ~16 msec time period
  connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
  /* If advance() exceeds its designated time slice, QTimer will skip
     timeout()-events. Effectively this gives variable frame rate by
     simply dropping frames. */

  addItem(new Ball{});
}

void GameScene::advance() {
  // FIXME: calculate time delta to synchronize simulation with real time
  world.stepSimulation(1.0 / 60.0);

  QGraphicsScene::advance(); // Advance items, i.e. render
}
