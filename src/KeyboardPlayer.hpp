#ifndef KEYBOARD_PLAYER_HPP
#define KEYBOARD_PLAYER_HPP

#include "Player.hpp"

#include <QTimer>
#include <map> // std::map
#include <functional> // std::function

/* Control the ball using the keyboard.

   This class uses QTimers to smooth out key repetition. Otherwise,
   holding down e.g. the left key would result in a left rotation
   followed by a delay before additional left rotations at an
   unspecified interval. */
class KeyboardPlayer : public Player {
  Q_OBJECT
public:
  KeyboardPlayer(GameScene* scene, Ball* ball, Qt::Key up, Qt::Key down,
                 Qt::Key left, Qt::Key right, Qt::Key apply);

  // Gets called by the scene when e.g. a keyEvent occurs
  virtual bool eventFilter(QObject * watched, QEvent * event);
private:
  // We need to store Qt::Key and look up int (from QKeyEvent::key),
  // thus we use int not Qt::Key for the key type
  std::map<int, QTimer*> timers;

  static const int kMillisecondsBetweenRepetitions;

  // Define Action to be a pointer to a member function of Player
  typedef void (Player::*Action)();

  // Sets up a timer and makes eventFilter recognize the key
  void registerKey(Qt::Key, Action);
};

#endif
