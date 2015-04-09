#include "GameScene.hpp"

#include "Ball.hpp"

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, 1280, 720, parent} // x, y, width, height
{
  addItem(new Ball{});
}
