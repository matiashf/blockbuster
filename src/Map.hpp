#ifndef MAP_HPP
#define MAP_HPP

#include <vector> // std::vector
#include <stdexcept> // std::exception
#include <QTextStream>
#include <QFileInfo>
#include <QRect>
#include <QString>
#include <QChar>

class GameScene; // Forward declaration

/** A class that parses a map file and loads it into a GameScene.

    The Map class parses a map file into an intermediate data
    structure without creating actual QGraphicItem objects. This makes
    it easier to write unit tests for the parser.
 */
class Map {
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
  Map(QTextStream* stream, QFileInfo* file_info=nullptr);
  void load(GameScene* scene);

  // Expose some internal structure to allow for testing
  inline int width() const { return width_; }
  inline int height() const { return height_; }
  inline const std::vector<QRect>* rects() const { return &rects_; };
  void parse();
};

#endif
