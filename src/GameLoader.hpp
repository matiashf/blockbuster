#ifndef GAME_LOADER_HPP
#define GAME_LOADER_HPP

#include <functional> // std::function
#include <vector> // std::vector
#include <QTextStream>

class GameScene; // Forward declaration

class GameLoader {
private:
  QTextStream* stream;
public:
  GameLoader(QTextStream*);

  std::vector<QRect> parse();
  void load(GameScene* scene);
};

#endif
