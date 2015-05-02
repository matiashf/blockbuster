#include "KeyboardPlayer.hpp"

#include <QKeyEvent>

// We're not concerned about avoiding multiple repetitive control
// actions on a single keypress, but about how the human player
// perceives the responsiveness of keyboard interaction. Thus the time
// between repeated actions value is very low, with the timer firing
// once for every every second frame of the game. Qt also aligns
// timers, so this will most likely be attached to the 60 Hz frame
// timer.
const int KeyboardPlayer::kMillisecondsBetweenRepetitions = 33; // results in 30Hz

KeyboardPlayer::KeyboardPlayer(GameScene* scene, Ball* ball, Qt::Key up,
                               Qt::Key down, Qt::Key left, Qt::Key right,
                               Qt::Key apply) :
  Player{scene, ball}
{
  registerKey(up, &KeyboardPlayer::increaseImpulse);
  registerKey(down, &KeyboardPlayer::decreaseImpulse);
  registerKey(left, &KeyboardPlayer::rotateLeft);
  registerKey(right, &KeyboardPlayer::rotateRight);
  registerKey(apply, &KeyboardPlayer::applyImpulse);
}

bool KeyboardPlayer::eventFilter(QObject * watched, QEvent * event) {
  Q_UNUSED(watched);

  if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

    if (keyEvent->isAutoRepeat())
      // Our own repeat timer for the key is already running.
      return true;  // Discard the event.

    auto iterator = timers.find(keyEvent->key());
    if (iterator == timers.end())
      return false;  // Not our key. Let someone else handle it.
    QTimer* timer = iterator->second; // the maps stores a (key, timer*) pair

    if (event->type() == QEvent::KeyPress) {
      timer->start();
      // Fire the timer right away, bypassing the protected
      // restriction on timeout().  A better alternative would be to
      // subclass QTimer to make an ImmediateTimer with an overridden
      // start() method.
      QMetaObject::invokeMethod(timer, "timeout"); // timer->timeout()
    } else { // (event->type() == QEvent::KeyRelease)
      timer->stop();
    }

    return true;  // Stop processing the event (because it was handled here)
  }

  return false;  // Continue processing the event
}

void KeyboardPlayer::registerKey(Qt::Key key, Action action) {
  QTimer* timer = new QTimer(this);
  timer->setInterval(kMillisecondsBetweenRepetitions);
  connect(timer, &QTimer::timeout, this, action);
  timers.emplace(key, timer);
}
