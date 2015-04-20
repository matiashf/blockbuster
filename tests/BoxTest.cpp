#include <gtest/gtest.h>

#include "GameSceneTest.hpp"
#include "Box.hpp"

class BoxTest : public GameSceneTest {};

TEST_F(BoxTest, addBox) {
  scene.addItem(new Box{0, 0, scene.width(), scene.height()});
}
