#include "GameLoader.hpp"
#include "GameScene.hpp"
#include "Box.hpp"

#include <vector> // std::vector

GameLoader::GameLoader(QTextStream* stream_) :
  stream{stream_},
  width_{0},
  height_{0}
{
}

void GameLoader::parse() {
  std::vector<QRect> partial_boxes; // Boxes during parsing
}

void GameLoader::load(GameScene* scene) {
  scene->addItem(new Box{0, 0, scene->width(), scene->height()});
}
