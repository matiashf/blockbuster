#include "GameScene.hpp"
#include "Ball.hpp"
#include "Box.hpp"

// The meaning of these constants are explained in the header file.
const int GameScene::kMaxVelocityIterations = 1;
const int GameScene::kMaxPositionIterations = 1;

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, 1920, 1080, parent}, // x, y, width, height. Full HD.
  timer{new QTimer{this}},
  gravity{0.0f, 9.81f}, // Earth gravity
  world_{gravity},
{
  timeAccumulator.start(); // For synchronizing the physics engine with real time
  setBackgroundBrush(QBrush{Qt::black});

  connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
  /* If advance() exceeds its designated time slice, QTimer will skip
     timeout()-events. Effectively this gives variable frame rate by
     simply dropping frames. */
  timer->start(1000.0 / 60.0); // 60 FPS => ~16 msec time period

  addItem(new Ball{width() / 2, height() / 2, 5});
  addItem(new Box{width() / 2, height() / 2, 10, 10});
}

void GameScene::advance() {
  // The timeAccumulator returns milliseconds, but the step function takes seconds
  world()->Step(timeAccumulator.restart() / 1000.0f,
             kMaxVelocityIterations, kMaxPositionIterations);

  QGraphicsScene::advance(); // Advance items, i.e. render
}
