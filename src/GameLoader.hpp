#ifndef GAME_LOADER_HPP
#define GAME_LOADER_HPP

#include <functional> // std::function
#include <vector> // std::vector
#include <QIODevice>

class GameScene; // Forward declaration

class GameLoader {
private:
  QIODevice& input;
public:
  GameLoader(QIODevice&);

  std::vector<QRect> parse();
  void load(GameScene* scene);
};

#endif
