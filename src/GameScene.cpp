#include "GameScene.hpp"
#include "Ball.hpp"
#include "Box.hpp"
#include "Arrow.hpp"
#include "Player.hpp"
#include "KeyboardPlayer.hpp"

#include <Box2D.h>
#include <cmath> // pow
#include <QFile>
#include <QTextStream>
#include <Qt> // Qt::FindDirectChildrenOnly

// The meaning of these constants are explained in the header file.
const int GameScene::kMaxVelocityIterations = 1;
const int GameScene::kMaxPositionIterations = 1;
const float GameScene::kScaleFactor = 2.0f; // => world size ~ 35m x 20m
const qreal GameScene::kFrameRate = 60.0; // 60 FPS => ~16 ms between frames
const int GameScene::kSceneHeight = 1080; // Full HD
const int GameScene::kSceneWidth = kSceneHeight * 16 / 9;

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, kSceneWidth, kSceneHeight, parent},
  timer{new QTimer{this}},
  gravity{0.0f, 9.81f}, // Earth gravity
  world_{gravity},
  worldScale{ 0.5f * gravity.y * pow(kScaleFactor, 2) / height()} // meters/pixel
{
  world()->SetContactListener(&contact_listener);

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

  Ball* b1 = new Ball{0, 0, 25.0f};
  addItem(b1);
  new KeyboardPlayer(this, b1, Qt::Key_W, Qt::Key_S, Qt::Key_A, Qt::Key_D, Qt::Key_Space);
  Ball* b2 = new Ball{width() - 50.0f, 0, 25.0f};
  addItem(b2);
  new KeyboardPlayer(this, b2, Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right, Qt::Key_Return);
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
  clock.start(); // Reset the clock
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
  timestep_ = milliseconds / 1000.0f; // Seconds
  world()->Step(timestep_, kMaxVelocityIterations, kMaxPositionIterations);

  QGraphicsScene::advance(); // Advance items, i.e. update positions and render
}

void GameScene::advance() {
  advance(clock.restart());
}

bool GameScene::eventFilter(QObject * watched, QEvent * event) {
  QList<Player *> players = findChildren<Player *>(QString(),
                                                   Qt::FindDirectChildrenOnly);

  for (Player* player : players)
    if (player->eventFilter(watched, event))
      return true; // The event was not processed
  return false; // The event was processed
}
