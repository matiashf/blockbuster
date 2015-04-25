#ifndef GAME_LOADER_HPP
#define GAME_LOADER_HPP

#include <QFile>

class QGraphicsItem; // Forward declaration

class GameLoader {
private:
  QIODevice& input;
public:
  GameLoader(QIODevice&);

  operator bool() const;
  GameLoader& operator++();
  QGraphicsItem* operator*() const;
};

#endif
