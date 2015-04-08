#include "GameView.hpp"

#include <QGLFormat>

#include <btBulletDynamicsCommon.h>

GameView::GameView(GameScene* scene_, QWidget* parent) :
  QGraphicsView{scene_, parent}
{
  // Enable OpenGL rendering and use antialiasing
  setViewport(new QGLWidget{QGLFormat(QGL::SampleBuffers)});
  // setViewport transfers ownership of QGLWidget, deleted in destructor

  // Expand to fill parent container, never go below minimum size
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  setMinimumSize(scene()->width(), scene()->height());
  setFrameShape(QFrame::NoFrame); // Hide 1px border, avoid scrollbars
}

void GameView::resizeEvent(QResizeEvent * event) {
  // Scale the view to fit the entire scene
  fitInView(sceneRect(), Qt::KeepAspectRatio);
}
