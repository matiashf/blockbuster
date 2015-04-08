#ifndef GAME_WIDGET_HPP
#define GAME_WIDGET_HPP

#include <QtWidgets/QGraphicsView>

#include "GameScene.hpp"

class GameWidget : public QGraphicsView {
  Q_OBJECT

public:
  GameWidget(GameScene* scene, QWidget* parent=0);
};

#endif