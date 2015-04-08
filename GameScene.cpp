#include "GameScene.hpp"

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{0, 0, 800, 600, parent} // x, y, width, height
{
  setBackgroundBrush(Qt::blue);
}
