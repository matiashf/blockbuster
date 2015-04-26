#ifndef GAME_LOADER_HPP
#define GAME_LOADER_HPP

#include <vector> // std::vector
#include <QTextStream>
#include <QRect>

class GameScene; // Forward declaration

class GameLoader {
private:
  QTextStream* stream;
  int width_, height_; // in units of characters
  std::vector<QRect> rects_; // Parsed rects
public:
  GameLoader(QTextStream*);
  void load(GameScene* scene);

  // Expose some internal structure to allow for testing
  inline int width() const { return width_; }
  inline int height() const { return height_; }
  inline const std::vector<QRect>* rects() const { return &rects_; };
  void parse();
};

#endif
