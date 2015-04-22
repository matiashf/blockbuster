#include <gtest/gtest.h>

#include "GameSceneTest.hpp"
#include "Ball.hpp"

class BallTest : public GameSceneTest {
protected:
  Ball* ball;
  qreal radius = 50.0d;
public:
  BallTest() :
    // Create a ball in the top left corner
    ball{new Ball{0, 0, radius}}
  {
    scene.addItem(ball);
  }
};

TEST_F(BallTest, coordinate_interpretation) {
  // The constructor should interpret the position given to it as the
  // top left corner of the rectangle containing the cicle. The origin
  // of the ball reference system, however, should be at the center of
  // the ball (so that it corresponds with the center of mass).
  EXPECT_DOUBLE_EQ(radius, ball->x());
  EXPECT_DOUBLE_EQ(radius, ball->y());
}

TEST_F(BallTest, radius) {
  EXPECT_DOUBLE_EQ(radius, ball->radius());
}
