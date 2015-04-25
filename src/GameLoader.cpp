#include "GameLoader.hpp"

GameLoader::GameLoader(QIODevice& input_) :
  input{input_}
{
}

GameLoader::operator bool() const {
  // FIXME
  return false;
}

GameLoader& GameLoader::operator++() {
  // FIXME
  return *this;
}

QGraphicsItem* GameLoader::operator*() const {
  // FIXME
  return nullptr;
}
