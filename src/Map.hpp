#ifndef MAP_HPP
#define MAP_HPP

#include <vector> // std::vector
#include <stdexcept> // std::exception
#include <QTextStream>
#include <QRect>
#include <QString>
#include <QChar>
#include <QPoint>

class GameScene; // Forward declaration

/** A class that parses a map file and loads it into a GameScene.

    The Map class parses a map file into an intermediate data
    structure without creating actual QGraphicItem objects. This makes
    it easier to write unit tests for the parser.

    Instead of telling the scene to load the map, we tell the map to
    load itself into the scene. This makes it possible for the scene
    to not know anything about the items placed in it (reducing
    coupling).
 */
class Map {
private:
  QString filename;
  int width_, height_; // in units of characters
  std::vector<QRect> rects_; // Parsed rects
  std::vector<QPoint> balls_; // Parsed balls
  QRect* current; // The rect currently open on this line

  QString line; // The current line, used in error message
  int lineNo, linePos; // Lines count from 1, positions within line from 0

  std::exception error(const char*);
  void parse(int x, int y, QChar symbol);
  void parse(QTextStream* stream);
public:
  /// Convenience constructor calls Map{QString{map_url}}
  Map(const char* map_url);
  /// Opens and parses the file at the given path/url
  Map(QString map_url);
  /// Parses from the given QTextStream. Used in tests.
  Map(QTextStream* stream);
  /// Create items on the scene based on the parsed map
  void loadInto(GameScene* scene) const;

  // Expose some internal structure to allow for testing
  inline int width() const { return width_; }
  inline int height() const { return height_; }
  inline const std::vector<QRect>* rects() const { return &rects_; };
  inline const std::vector<QPoint>* balls() const { return &balls_; };

  /// Returns a list of the urls for all builtin maps
  static QStringList all();
  /// Returns the url for a random builtin map
  static QString random();
};

#endif
