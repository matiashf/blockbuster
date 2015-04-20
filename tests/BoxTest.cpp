#include <gtest/gtest.h>

#include "GameSceneTest.hpp"
#include "Box.hpp"

class BoxTest : public GameSceneTest {};

TEST_F(BoxTest, interpret_coordinates_as_position_of_top_left_corner) {
  // Create a box that fills the entire scene
  Box* box = new Box{0, 0, scene.width(), scene.height()};
  scene.addItem(box);

  // The coordinates given to the box constructor should be
  // interpreted as the x and y coordinates of the top left corner of
  // the box. After creating the box, the x() and y() parameters
  // should return the position of the center of the box.
  EXPECT_DOUBLE_EQ(scene.width() / 2.0, box->x());
  EXPECT_DOUBLE_EQ(scene.height() / 2.0, box->y());
}
