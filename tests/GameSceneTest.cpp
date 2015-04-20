#include <gtest/gtest.h>

#include "GameSceneTest.hpp"

TEST_F(GameSceneTest, world_has_same_origin_as_scene) {
  EXPECT_DOUBLE_EQ(scene.mapToWorld(0), 0);
  EXPECT_DOUBLE_EQ(scene.mapFromWorld(0), 0);
}
