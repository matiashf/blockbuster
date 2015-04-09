#include "GameScene.hpp"
#include "Ball.hpp"

#include <QTimer>

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, 1280, 720, parent}, // x, y, width, height
  timer{new QTimer{this}}
{
  timer->start(1000.0 / 60.0); // 60 FPS => ~16 msec time period
  connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
  /* If advance() exceeds its designated time slice, QTimer will skip
     timeout()-events. Effectively this gives variable frame rate by
     simply dropping frames. */
  // TODO: Connect timer to physics engine

  addItem(new Ball{});
}
