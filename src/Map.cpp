#include "Map.hpp"
#include "GameScene.hpp"
#include "Box.hpp"
#include "Ball.hpp"

#include <iostream> // std::cerr

Map::Map(QTextStream* stream_, QFileInfo* file_info_) :
  stream{stream_},
  file_info{file_info_},
  current{nullptr}
{
}

/** Print a helpful error message and return an exception. */
std::exception Map::error(const char * description) {
  // FIXME: subclass runtime_exception and allow errors to be programmatically examined
  std::cerr << "Error: " << description << std::endl;
  if (file_info != nullptr)
    std::cerr << "In file " << file_info->absoluteFilePath().toStdString() << ", ";
  std::cerr << "on line " << lineNo << ", character " << linePos << ":" << std::endl;
  std::cerr << line.toStdString() << std::endl;
  std::cerr << std::string(linePos, ' ') << '^' << std::endl;
  return std::runtime_error(description);
}

/** Parse the given symbol at map position (x, y) */
void Map::parse(int x, int y, QChar symbol) {
  constexpr QChar hash{'#'}, space{' '}, dash{'-'};

  if (current != nullptr and ((symbol == dash and x != width() - 1) or (symbol == hash and current->width() > 1))) {
    current->setRight(current->right() + 1);
    if (symbol == hash)
      current = nullptr;
  } else if (symbol == hash) {
    rects_.emplace_back(x, y, 1, 1); // Emplace: construct in place
    current = &rects_.back();
  } else if (symbol != space) {
    throw error("Unexpected symbol inside map");
  }
}

/** Parse the overall structure of the map and delegate to parse(x, y, symbol). */
void Map::parse() {
  QChar slash{'/'}, backslash{'\\'}, dash{'-'}, bar{'|'};

  lineNo = 1;
  linePos = 0;
  width_ = 0;
  height_ = 0;

  // Discard all lines until we find a line beginning with a slash
  while (true) {
    line = stream->readLine();
    if (line.isNull())
      throw error("Could not find a line beginning with a slash (/)");
    else if (line.startsWith(slash))
      break;
    else
      ++lineNo;
  }

  // The line starts with a slash. Expecting a /----\ header
  for (linePos = 1; ; linePos++) {
    if (linePos == line.length())
      throw error("Unexpected end of line while parsing map header");
    QChar current = line[linePos];
    if (current == dash)
      ++width_;
    else if (current == backslash)
      break;
    else
      throw error("Unexpected symbol while parsing map header. Expected dash (-) or slash (/).");
  }

  // Parsing lines of the map |...| until the end \-----/
  while (true) {
    ++lineNo;
    linePos = 0;
    line = stream->readLine();
    if (line.isNull())
      throw error("Missing map footer");
    else if (line.startsWith(backslash))
      break;
    else if (!line.startsWith(bar))
      throw error("Unexpected symbol at beginning of line in map body. Expected bar (|)");
    else if (line.length() < width_ + 2) {
      linePos = line.length();
      throw error("Unexpected end of file in map body.");
    }
    ++height_;
    for (linePos=1; linePos < width_ + 1; ++linePos)
      parse(linePos - 1, height_ - 1, line[linePos]);
    if (line[linePos] != bar)
      throw error("Unexpected symbol at end of line in map body. Expected bar (|).");
  }

  // The last line of the map, something like this: \-----/
  // We already know the line starts with a backslash
  if (line.length() < width_ + 2) {
    linePos = line.length();
    throw error("Unexpected end of file in map footer.");
  }
  for (linePos = 1; linePos < width_ + 1; ++linePos)
    if (line[linePos] != dash)
      throw error("Unexpected symbol in map footer. Expected dash (-).");
  if (line[linePos] != slash)
    throw error("Unexpected end of map footer. Expected slash (/).");

  // All lines after the end of the map are ignored
}

void Map::load(GameScene* scene) {
  parse();
  qreal width_scale = scene->width() / width();
  qreal height_scale = scene->height() / height();

  for (auto i = rects_.cbegin(); i != rects_.cend(); ++i) {
    const QRect& r = *i;
    // FIXME: Connect the box to a ball
    scene->addItem(new Box{r.x() * width_scale, r.y() * height_scale,
                           r.width() * width_scale, r.height() * height_scale});
  }
}
