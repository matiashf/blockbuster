#ifndef GAME_ITEM_HPP
#define GAME_ITEM_HPP

#include "GameScene.hpp"

#include <QGraphicsItem>

/** A small convenience class for accessing the game scene from items. */
class GameItem : public QGraphicsItem {
public:
  using QGraphicsItem::QGraphicsItem;
  /** Cast the containing scene to GameScene. Returns nullptr if no
      scene or if the containing scene is not a GameScene. */
  inline GameScene* gameScene() { return dynamic_cast<GameScene*>(scene()); }
  // TODO: Throw an exception if the game item is added to a non game scene
};

#endif
