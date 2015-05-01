#include "KeyboardPlayer.hpp"

#include <QKeyEvent>

bool KeyboardPlayer::eventFilter(QObject * watched, QEvent * event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    switch (keyEvent->key()) {
    case Qt::Key_Up:
      increaseImpulse();
      break;
    case Qt::Key_Down:
      decreaseImpulse();
      break;
    case Qt::Key_Left:
      rotateLeft();
      break;
    case Qt::Key_Right:
      rotateRight();
      break;
    case Qt::Key_Space:
      applyImpulse();
      break;
    default:
      return false;  // Continue processing the event
    }
    return true;  // Stop processing the event
  }

  return false;  // Continue processing the event
}
