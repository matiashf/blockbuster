#include "GameView.hpp"

#include <QGLFormat>

GameView::GameView(GameScene* scene_, QWidget* parent) :
  QGraphicsView{scene_, parent}
{
  // Enable OpenGL rendering and use antialiasing
  setViewport(new QGLWidget{QGLFormat(QGL::SampleBuffers)});
  // setViewport transfers ownership of QGLWidget, deleted in destructor

  // Expand to fill parent container, never go below minimum size
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  setMinimumSize(1280, 720); // HD resolution
  setFrameShape(QFrame::NoFrame); // Hide 1px border, avoid scrollbars
}

void GameView::resizeEvent(QResizeEvent * event) {
  // Scale the view to fit the entire scene
  fitInView(sceneRect(), Qt::KeepAspectRatio);
  Q_UNUSED(event); // Supress compiler warning about unused variable
}

void GameView::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
  case Qt::Key_F:
    showFullScreen();
    break;
  case Qt::Key_Escape:
    showNormal();
    break;
  case Qt::Key_Q:
    close();
    break;
  case Qt::Key_Space:
    ((GameScene *) scene())->toggle();
    break;
  case Qt::Key_S:
    ((GameScene *) scene())->advance(10.0d); // milliseconds
    break;
  default:
    event->ignore();
  }
}