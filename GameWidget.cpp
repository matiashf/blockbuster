#include "GameWidget.hpp"

#include <btBulletDynamicsCommon.h>

GameWidget::GameWidget(QWidget* parent) :
  QGraphicsView(parent)
{
  setMinimumSize(800, 600); // width, height

  // Expand to fill parent container, never go below minimum size
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}
