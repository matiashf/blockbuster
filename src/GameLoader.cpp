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
  parse();
  qreal width_scale = scene->width() / width();
  qreal height_scale = scene->height() / height();

  for (auto i = rects_.cbegin(); i != rects_.cend(); ++i) {
    const QRect& r = *i;
    scene->addItem(new Box{r.x() * width_scale, r.y() * height_scale,
                           r.width() * width_scale, r.height() * height_scale});
  }
}
