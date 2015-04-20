#include "GameScene.hpp"
#include "Ball.hpp"
#include "Box.hpp"

#include <cmath>

// The meaning of these constants are explained in the header file.
const int GameScene::kMaxVelocityIterations = 1;
const int GameScene::kMaxPositionIterations = 1;
const float GameScene::kScaleFactor = 2.0f; // => world size ~ 35m x 20m
const qreal GameScene::kFrameRate = 60.0; // 60 FPS => ~16 ms between frames

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, 1920, 1080, parent}, // x, y, width, height. Full HD.
  timer{new QTimer{this}},
  gravity{0.0f, 9.81f}, // Earth gravity
  world_{gravity},
  worldScale{ 0.5f * gravity.y * pow(kScaleFactor, 2) / height()} // meters/pixel
{
  setBackgroundBrush(QBrush{Qt::black});

  timer->setInterval(1000.0 / kFrameRate);
  connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
  /* If advance() exceeds its designated time slice, QTimer will skip
     timeout()-events. Effectively this gives variable frame rate by
     simply dropping frames. */
}

void GameScene::start() {
  worldTime.start();
  timer->start(); // Start calling advance()
}

void GameScene::stop() {
  timer->stop(); // Stop calling advance()
}

void GameScene::toggle() {
  if (timer->isActive())
    stop();
  else
    start();
}

void GameScene::advance(qreal milliseconds) {
  world()->Step(milliseconds / 1000.0f, // The Step function takes seconds
                kMaxVelocityIterations, kMaxPositionIterations);

  QGraphicsScene::advance(); // Advance items, i.e. update positions and render
}

void GameScene::advance() {
  advance(worldTime.restart());
}
