#include "GameLoader.hpp"
#include "GameScene.hpp"
#include "Box.hpp"

#include <vector> // std::vector
#include <QRect>

GameLoader::GameLoader(QIODevice& input_) :
  input{input_}
{
}

std::vector<QRect> parse() {
  std::vector<QRect> partial_boxes; // Boxes during parsing
  std::vector<QRect> boxes; // Parsed boxes
  return boxes;
}

void GameLoader::load(GameScene* scene) {
  scene->addItem(new Box{0, 0, scene->width(), scene->height()});
}
