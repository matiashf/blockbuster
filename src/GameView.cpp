#include "GameView.hpp"
#include "GameScene.hpp"
#include "Ball.hpp"
#include "ImpulseVectorItem.hpp"

#include <QGLFormat>

GameView::GameView(GameScene* scene_, QWidget* parent) :
  QGraphicsView{scene_, parent}
{
  // Enable OpenGL rendering and use antialiasing
  setRenderHint(QPainter::Antialiasing);
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
  case Qt::Key_P:
    ((GameScene *) scene())->toggle();
    break;
  case Qt::Key_S:
    ((GameScene *) scene())->advance(10.0d); // milliseconds
    break;
  case Qt::Key_Up:
    ((GameScene *) scene())->ball()->impulseVector()->increase();
    break;
  case Qt::Key_Down:
    ((GameScene *) scene())->ball()->impulseVector()->decrease();
    break;
  case Qt::Key_Left:
    ((GameScene *) scene())->ball()->impulseVector()->rotateLeft();
    break;
  case Qt::Key_Right:
    ((GameScene *) scene())->ball()->impulseVector()->rotateRight();
    break;
  case Qt::Key_Space:
    ((GameScene *) scene())->ball()->applyImpulse();
    break;
  default:
    event->ignore();
  }
}
