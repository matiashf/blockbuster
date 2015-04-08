#include "GameScene.hpp"

GameScene::GameScene(QObject* parent) :
  QGraphicsScene{parent}
{
  setBackgroundBrush(Qt::blue);
}
