#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <QtWidgets/QGraphicsView>
#include <QtGui/QKeyEvent>

#include "GameScene.hpp"

/** A widget class that displays the scene and sends key events. */
class GameView : public QGraphicsView {
  Q_OBJECT

public:
  /// Constructs the view.
  GameView(GameScene* scene, QWidget* parent=0);
  /// Scales the view so the entire scene is visible.
  void resizeEvent(QResizeEvent *);
  void keyPressEvent(QKeyEvent *);
};

#endif
