#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <QtWidgets/QGraphicsScene>

class GameScene: public QGraphicsScene {
  Q_OBJECT

public:
  GameScene(QObject* parent=0);
};

#endif
