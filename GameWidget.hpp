// -*- c++ -*-

#ifndef GAME_WIDGET_HPP
#define GAME_WIDGET_HPP

#include <QtWidgets/QGraphicsView>

class GameWidget : public QGraphicsView {
  Q_OBJECT

public:
  GameWidget(QWidget* parent=0);
};

#endif
