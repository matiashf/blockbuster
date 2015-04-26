#include <gtest/gtest.h>
#include <QTextStream>
#include <QIODevice> // QIODevice::ReadOnly

#include "GameLoader.hpp"

class GameLoaderTest : public ::testing::Test {
protected:
  QString string;
  QTextStream stream;
  GameLoader loader{&stream};

  void parse(const char * cstring) {
    string.clear();
    string.append(cstring);
    stream.setString(&string, QIODevice::ReadOnly);
    loader.parse();
  }

  void expect_parsed(const QRect& expected) {
    ASSERT_EQ(1, loader.rects()->size());
    const QRect& actual = loader.rects()->back();
    EXPECT_EQ(expected.x(), actual.x());
    EXPECT_EQ(expected.y(), actual.y());
    EXPECT_EQ(expected.width(), actual.width());
    EXPECT_EQ(expected.height(), actual.height());
  }
 
  void expect_dimensions(int width, int height) {
    EXPECT_EQ(width, loader.width());
    EXPECT_EQ(height, loader.height());
  }
};

TEST_F(GameLoaderTest, single_box_filling_entire_scene) {
  parse(R"(
/-\
|#|
\-/
)");
  expect_parsed(QRect{0, 0, 1, 1});
  expect_dimensions(1, 1);
}

TEST_F(GameLoaderTest, single_box_with_whitespace_under_and_after) {
  parse(R"(
/--\
|# |
|  |
\--/
)");
  expect_parsed(QRect{0, 0, 1, 1});
  expect_dimensions(2, 2);
}
