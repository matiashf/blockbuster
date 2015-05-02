#include "KeyboardPlayer.hpp"

#include <QKeyEvent>

KeyboardPlayer::KeyboardPlayer(GameScene* scene, Ball* ball, Qt::Key up,
                               Qt::Key down, Qt::Key left, Qt::Key right,
                               Qt::Key apply) :
  Player{scene, ball},
  up_key{up},
  down_key{down},
  left_key{left},
  right_key{right},
  apply_key{apply}
{
}

bool KeyboardPlayer::eventFilter(QObject * watched, QEvent * event) {
  Q_UNUSED(watched);
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    int key = keyEvent->key();
    if (key == up_key)
      increaseImpulse();
    else if (key == down_key)
      decreaseImpulse();
    else if (key == left_key)
      rotateLeft();
    else if (key == right_key)
      rotateRight();
    else if (key == apply_key)
      applyImpulse();
    else
      return false;  // Continue processing the event
    return true;  // Stop processing the event (because it was handled here)
  }

  return false;  // Continue processing the event
}
