#include <gtest/gtest.h>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  QApplication application{argc, argv};
  return RUN_ALL_TESTS();
}
