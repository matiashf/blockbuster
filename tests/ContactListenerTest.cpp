#include <gtest/gtest.h>

#include <Box2D/Common/b2Settings.h>

TEST(ContactListenerTest, b2d_assumptions) {
  ASSERT_EQ(2, b2_maxManifoldPoints); // Collisions occur between exactly two bodies
}
