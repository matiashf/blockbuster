#include "GameWidget.hpp"

#include <btBulletDynamicsCommon.h>

GameWidget::GameWidget(GameScene* scene_, QWidget* parent) :
  QGraphicsView{scene_, parent}
{
  // FIXME: Use OpenGl for rendering. Remember destructor.
  //setViewport(new QGLWidget{QGLFormat(QGL::SampleBuffers)});

  // Expand to fill parent container, never go below minimum size
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  setMinimumSize(scene()->width(), scene()->height());
  setFrameShape(QFrame::NoFrame); // Hide 1px border, avoid scrollbars
}
