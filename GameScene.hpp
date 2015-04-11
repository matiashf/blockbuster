#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <QtWidgets/QGraphicsScene>
#include <QTimer>
#include <QTime>

class GameScene: public QGraphicsScene {
  Q_OBJECT
private:
  QTimer* timer; // Periodic event dispatcher
  QTime timeAccumulator; // Clock

  /* Use a constraint-based physics engine, like this:
     http://allenchou.net/2013/12/game-physics-constraints-sequential-impulse
  */
public:
  GameScene(QObject* parent=0);
public slots:
  void advance();
};

#endif
