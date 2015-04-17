#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <QtWidgets/QGraphicsView>
#include <QtGui/QKeyEvent>

#include "GameScene.hpp"

class GameView : public QGraphicsView {
  Q_OBJECT

public:
  GameView(GameScene* scene, QWidget* parent=0);
  void resizeEvent(QResizeEvent *);
  void keyPressEvent(QKeyEvent *);
};

#endif
