#include "GameScene.hpp"

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, 1280, 720, parent} // x, y, width, height
{
  setBackgroundBrush(Qt::blue);
}
