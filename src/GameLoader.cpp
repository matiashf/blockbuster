#include "GameLoader.hpp"
#include "GameScene.hpp"
#include "Box.hpp"

#include <iostream> // std::cerr

GameLoader::GameLoader(QTextStream* stream_) :
  stream{stream_},
  width_{0},
  height_{0}
{
}

std::exception GameLoader::error(const char * description) {
  // FIXME: subclass runtime_exception and allow errors to be programmatically examined
  std::cerr << "Error: " << description << std::endl;
  std::cerr << "on line " << lineNo << ", character " << linePos << ":" << std::endl;
  std::cerr << line.toStdString() << std::endl;
  std::cerr << std::string(linePos - 1, ' ') << '^' << std::endl;
  return std::runtime_error(description);
}

void GameLoader::parse(int x, int y, QChar symbol) {
  QChar hash{'#'};
  if (symbol ==  hash)
    rects_.push_back(QRect{x, y, 1, 1});
  else
    throw error("Unexpected symbol");
}

void GameLoader::parse() {
  QChar slash{'/'}, backslash{'\\'}, dash{'-'}, bar{'|'};

  lineNo = 1;
  linePos = 0;

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
      throw error("Unexpected end of line");
    QChar current = line[linePos];
    if (current == dash)
      ++width_;
    else if (current == backslash)
      break;
    else
      throw error("Unexpected symbol");
  }

  // Parsing lines of the map |...| until the end \-----/
  while (true) {
    ++lineNo;
    linePos = 0;
    line = stream->readLine();
    if (line.isNull())
      throw error("Unexpected end of file");
    else if (line.startsWith(backslash))
      break;
    else if (!line.startsWith(bar))
      throw error("Unexpected symbol");
    else if (line.length() < width_ + 2) {
      linePos = line.length();
      throw error("Unexpected end of file");
    }
    ++height_;
    for (linePos=1; linePos < width_ + 2; ++linePos)
      parse(linePos - 1, height_ - 1, line[linePos]);
    if (line[linePos] != bar)
      throw error("Unexpected symbol");
  }

  // The last line of the map, something like this: \-----/
  // We already know the line starts with a backslash
  if (line.length() < width_ + 2) {
    linePos = line.length();
    throw error("Unexpected end of file");
  }
  for (linePos = 1; linePos < width_ + 2; ++linePos)
    if (line[linePos] != dash)
      throw error("Unexpected symbol");
  if (line[linePos] != slash)
    throw error("Unexpected symbol");

  // All lines after the end of the map are ignored
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
