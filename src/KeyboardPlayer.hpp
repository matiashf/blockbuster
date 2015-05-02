#ifndef KEYBOARD_PLAYER_HPP
#define KEYBOARD_PLAYER_HPP

#include "Player.hpp"

class KeyboardPlayer : public Player {
  Q_OBJECT
public:
  KeyboardPlayer(GameScene* scene, Ball* ball, Qt::Key up, Qt::Key down,
                 Qt::Key left, Qt::Key right, Qt::Key apply);
  virtual bool eventFilter(QObject * watched, QEvent * event);
private:
  Qt::Key up_key;
  Qt::Key down_key;
  Qt::Key left_key;
  Qt::Key right_key;
  Qt::Key apply_key;
};

#endif
