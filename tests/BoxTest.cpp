#include <gtest/gtest.h>

#include "GameSceneTest.hpp"
#include "Box.hpp"

class BoxTest : public GameSceneTest {
protected:
  Box* box;
public:
  BoxTest() :
    // Create a box that fills the entire scene
    box{new Box{0, 0, scene.width(), scene.height()}}
  {
    scene.addItem(box);
  }
};

TEST_F(BoxTest, interpret_constructor_coordinates_as_position_of_top_left_corner) {
  // The coordinates given to the box constructor should be
  // interpreted as the x and y coordinates of the top left corner of
  // the box. After creating the box, the x() and y() parameters
  // should return the position of the center of the box.
  EXPECT_DOUBLE_EQ(scene.width() / 2.0, box->x());
  EXPECT_DOUBLE_EQ(scene.height() / 2.0, box->y());
}

TEST_F(BoxTest, width_and_height) {
  EXPECT_DOUBLE_EQ(scene.width(), box->width());
  EXPECT_DOUBLE_EQ(scene.height(), box->height());
}
