#include <gtest/gtest.h>

#include "GameSceneTest.hpp"

#include "Box.hpp"

TEST_F(GameSceneTest, world_has_same_origin_as_scene) {
  EXPECT_DOUBLE_EQ(0, scene.mapToWorld(0));
  EXPECT_DOUBLE_EQ(0, scene.mapFromWorld(0));
}

TEST_F(GameSceneTest, world_has_ground) {
  Box* box = new Box{0, 0, scene.width(), scene.height()};
  scene.addItem(box);
  double originalVerticalPosition = box->y();
  scene.advance(1000.0d); // milliseconds
  // Allow some leeway in the position. Box2D allows shapes to overlap
  // slightly. Less than 1 pixel movement is acceptable.
  EXPECT_NEAR(originalVerticalPosition, box->y(), 1.0f);
}
