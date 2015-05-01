#include "Player.hpp"
#include "Ball.hpp"
#include "Arrow.hpp"
#include "GameScene.hpp"

Player::Player(GameScene* scene, Ball* ball) :
  QObject{scene},
  ball_{ball}
{
}

GameScene* Player::scene() const {
  return dynamic_cast<GameScene*>(parent());
}

void Player::applyImpulse() {
  ball()->applyImpulse();
}

void Player::increaseImpulse() {
  ball()->arrow()->increase();
}

void Player::decreaseImpulse() {
  ball()->arrow()->decrease();
}

void Player::rotateLeft() {
  ball()->arrow()->rotateLeft();
}

void Player::rotateRight() {
  ball()->arrow()->rotateRight();
}
