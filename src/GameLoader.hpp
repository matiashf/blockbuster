#ifndef GAME_LOADER_HPP
#define GAME_LOADER_HPP

#include <vector> // std::vector
#include <stdexcept> // std::exception
#include <QTextStream>
#include <QFileInfo>
#include <QRect>
#include <QString>
#include <QChar>

class GameScene; // Forward declaration

/** A helper class for parsing and loading map files.

    The helper gets called by GameScene::load. This class was created
    to simplify testing and reduce code duplication.
 */
class GameLoader {
private:
  QTextStream* stream;
  QFileInfo* file_info;
  int width_, height_; // in units of characters
  std::vector<QRect> rects_; // Parsed rects
  QRect* current; // The rect currently open on this line

  QString line; // The current line, used in error message
  int lineNo, linePos; // Lines count from 1, positions within line from 0

  std::exception error(const char*);
  void parse(int x, int y, QChar symbol);
public:
  GameLoader(QTextStream* stream, QFileInfo* file_info=nullptr);
  void load(GameScene* scene);

  // Expose some internal structure to allow for testing
  inline int width() const { return width_; }
  inline int height() const { return height_; }
  inline const std::vector<QRect>* rects() const { return &rects_; };
  void parse();
};

#endif
