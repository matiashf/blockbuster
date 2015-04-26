#include <gtest/gtest.h>
#include <QDir>
#include <QString>

#include "GameSceneTest.cpp"

class MapTest : public GameSceneTest,
                public ::testing::WithParamInterface<QString> {
public:
  static QStringList all_maps() {
    QDir dir{":/maps/"};
    QStringList absolute_paths;
    for (QFileInfo i : dir.entryInfoList())
      absolute_paths.append(i.absoluteFilePath());
    return absolute_paths;
  }
};

INSTANTIATE_TEST_CASE_P(all_maps, MapTest,
                        ::testing::ValuesIn(MapTest::all_maps()));

#include <iostream>

TEST_P(MapTest, load) {
  // Simply load the map. We can't really test for anything else,
  // because this test gets run for every map. The intention is simply
  // to avoid shipping maps that crash the game.
  scene.load(GetParam());
}
