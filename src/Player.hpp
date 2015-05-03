#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>
#include <QEvent>

class GameScene;
class Ball;

/** An abstract class for controlling a ball.

    The player instance is used as an event filter by the scene, and
    is expected to react to events by implementing the eventFilter
    method. The ruturn value of eventFilter is as described in the Qt
    documentation: "In your reimplementation of this function, if you
    want to filter the event out, i.e. stop it being handled further,
    return true; otherwise return false."

    The Player is owned by scene and garbage collected by Qt.
*/
class Player : public QObject {
  Q_OBJECT
public:
  /// Constructs a player and transfers ownership to the scene
  Player(GameScene*, Ball*);

  // Accessors
  GameScene* scene() const;
  inline Ball* ball() const { return ball_; }
protected:
  // Methods for controlling the ball. Called by the player.
  void applyImpulse();
  void increaseImpulse();
  void decreaseImpulse();
  void rotateLeft();
  void rotateRight();
private:
  Ball* ball_;
};

#endif
