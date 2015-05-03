#include <gtest/gtest.h>
#include <QTextStream>
#include <QIODevice> // QIODevice::ReadOnly

#include "Map.hpp"

class MapTest : public ::testing::Test {
public:
  MapTest() : map{nullptr} {}
  ~MapTest() {
    if (map != nullptr)
      delete map;
  }
protected:
  Map* map;

  void parse(const char * cstring) {
    ASSERT_TRUE(map == nullptr);

    QString string{cstring};
    QTextStream stream{&string, QIODevice::ReadOnly};
    map = new Map{&stream};
  }

  void expect_parsed(const QRect& expected) {
    ASSERT_TRUE(map != nullptr);
    ASSERT_EQ(1, map->rects()->size());
    const QRect& actual = map->rects()->back();
    EXPECT_EQ(expected.x(), actual.x());
    EXPECT_EQ(expected.y(), actual.y());
    EXPECT_EQ(expected.width(), actual.width());
    EXPECT_EQ(expected.height(), actual.height());
  }
 
  void expect_dimensions(int width, int height) {
    ASSERT_TRUE(map != nullptr);
    EXPECT_EQ(width, map->width());
    EXPECT_EQ(height, map->height());
  }
};

TEST_F(MapTest, single_box_filling_entire_scene) {
  parse(R"(
/-\
|#|
\-/
)");
  expect_parsed(QRect{0, 0, 1, 1});
  expect_dimensions(1, 1);
}

TEST_F(MapTest, single_box_with_whitespace_under_and_after) {
  parse(R"(
/--\
|# |
|  |
\--/
)");
  expect_parsed(QRect{0, 0, 1, 1});
  expect_dimensions(2, 2);
}

TEST_F(MapTest, horizontal_box) {
  parse(R"(
/---\
|#-#|
\---/
)");
  expect_parsed(QRect{0, 0, 3, 1});
  expect_dimensions(3, 1);
}
