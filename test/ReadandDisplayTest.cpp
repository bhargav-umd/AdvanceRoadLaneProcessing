#include "../include/LaneDetector.hpp"
#include "../include/LanePredictor.hpp"
#include "../include/ReadAndDisplay.hpp"
#include <gtest/gtest.h>

ReadAndDisplay rdtest("../Dataset/Dataset2.mp4", "../Output/LaneDetector.avi");
TEST(ReadAndDisplayTest, readtest) {
  rdtest.read();

  EXPECT_EQ(rdtest.getFrameWidth(), 640);
  EXPECT_EQ(rdtest.getFrameHeight(), 480);
}
