#include <gtest/gtest.h>
#include <string> // std::string

#include "GameSceneTest.cpp"
#include "Map.hpp"

/* Use std::string instead of QString to get nicer error
   messages. QString doesn't play well with the google test framework
   (which uses c++ output streams) */

class MapFileTest : public GameSceneTest,
                    public ::testing::WithParamInterface<std::string> {
public:
  static std::vector<std::string> all_maps() {
    std::vector<std::string> absolute_paths;
    for (QString s : Map::all())
      absolute_paths.push_back(s.toStdString());
    return absolute_paths;
  }
};

INSTANTIATE_TEST_CASE_P(all_maps, MapFileTest,
                        ::testing::ValuesIn(MapFileTest::all_maps()));

TEST_P(MapFileTest, load) {
  // Simply load the map. We can't really test for anything else,
  // because this test gets run for every map. The intention is simply
  // to avoid shipping maps that crash the game.
  Map map{GetParam().c_str()};
  map.loadInto(&scene);
}
