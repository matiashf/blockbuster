#ifndef KEYBOARD_PLAYER_HPP
#define KEYBOARD_PLAYER_HPP

#include "Player.hpp"

class KeyboardPlayer : public Player {
  Q_OBJECT
public:
  using Player::Player;
  virtual bool eventFilter(QObject * watched, QEvent * event);
private:
};

#endif
