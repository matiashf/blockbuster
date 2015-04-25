#include "GameScene.hpp"
#include "Ball.hpp"
#include "Box.hpp"

#include <Box2D.h>
#include <cmath> // pow

// The meaning of these constants are explained in the header file.
const int GameScene::kMaxVelocityIterations = 1;
const int GameScene::kMaxPositionIterations = 1;
const float GameScene::kScaleFactor = 2.0f; // => world size ~ 35m x 20m
const qreal GameScene::kFrameRate = 60.0; // 60 FPS => ~16 ms between frames
const int GameScene::kSceneHeight = 1080; // Full HD
const int GameScene::kSceneWidth = kSceneHeight * 16 / 9;

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, kSceneWidth, kSceneHeight, parent},
  ball_{new Ball{width() / 2.0f - 12.5f, 0, 25.0f}},
  timer{new QTimer{this}},
  gravity{0.0f, 9.81f}, // Earth gravity
  world_{gravity},
  worldScale{ 0.5f * gravity.y * pow(kScaleFactor, 2) / height()} // meters/pixel
{
  setBackgroundBrush(QBrush{Qt::black});

  // Create static edges for the world, so that objects can't fall out.
  QRectF r = sceneRect();
  addEdgeLine(r.topLeft(), r.topRight());
  addEdgeLine(r.bottomLeft(), r.bottomRight());
  addEdgeLine(r.topLeft(), r.bottomLeft());
  addEdgeLine(r.topRight(), r.bottomRight());

  timer->setInterval(1000.0 / kFrameRate);
  connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
  /* If advance() exceeds its designated time slice, QTimer will skip
     timeout()-events. Effectively this gives variable frame rate by
     simply dropping frames. */

  addItem(ball());

  for (qreal x = 50.0d; x <= width() - 100.0d; x += 200.0d)
    for (qreal y = height() * 0.75d; y <= height() - 50.0d; y += 50.0d)
      addItem(new Box{x, y, 50.0f, 50.0f});
}

/** Create a static (non-moving) line between the two points. Used to
    create bounds for the scene (i.e. ground, walls and ceiling). */
void GameScene::addEdgeLine(QPointF from, QPointF to) {
  b2BodyDef edgeBodyDef;
  edgeBodyDef.position = mapToWorld(from);
  b2Body* edgeBody = world()->CreateBody(&edgeBodyDef); // FIXME: Free memory
  b2EdgeShape edgeShape;
  edgeShape.Set(b2Vec2(0,0), mapToWorld(to - from));
  edgeBody->CreateFixture(&edgeShape, 0.0f);
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
