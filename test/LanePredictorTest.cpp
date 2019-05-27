#include "../include/LanePredictor.hpp"
#include "../include/LaneDetector.hpp"
#include "../include/ReadAndDisplay.hpp"
#include <gtest/gtest.h>
cv::Mat testImage1 = cv::imread("../data/edge_image.jpg");
cv::Mat roied1 = cv::imread("../data/roitest.jpg");
cv::Mat frame1_ = cv::imread("../data/test.jpg");
cv::Mat right_Turn_frame = cv::imread("../data/rightturn.jpg");
cv::Mat left_Turn_frame = cv::imread("../data/leftturn.jpg");
/* LaneDetector ld_object(testImage); */
// cv::Mat edgess1 = ld_object.edgeDetector(testImage);
// cv::Mat roied_edges1 = ld_object.roiMaskSelection(testImage);
/*  */
TEST(LanePredictorTest, yellowTest) {
  LanePredictor lp(frame1_);
  cv::Vec4d yellow = lp.detectYellow();
  EXPECT_EQ(yellow[0], -637);
  EXPECT_EQ(yellow[1], 1128);
  EXPECT_EQ(yellow[2], 1068);
  EXPECT_EQ(yellow[3], -326);
}

TEST(LanePredictorTest, predictionTest) {
  LanePredictor lp(frame1_);
  cv::Vec4d yellow = lp.detectYellow();
  std::string prediction;
  prediction = lp.wrongLanePredictor(yellow);
  EXPECT_EQ(prediction, "Stay on this Lane!");

  cv::Vec4d points(120, -716, 556, 1481);
  EXPECT_EQ(lp.wrongLanePredictor(points), "Wrong Lane!!");
}

TEST(LanePredictorTest, turnPredictionTest1) {
  LanePredictor lp(frame1_);
  cv::Mat edgess = lp.edgeDetector(frame1_);
  cv::Mat roied = lp.roiMaskSelection(edgess);
  std::vector<std::vector<cv::Vec4i>> lanes(2);
  lanes = lp.houghTransform(roied);

  cv::Vec4d left{0, 0, 0, 0};
  cv::Vec4d right{0, 0, 0, 0};
  left = lp.lineFitting(lanes[0], frame1_);
  right = lp.lineFitting(lanes[1], frame1_);
  std::string prediction = lp.predictTurn(left, right, frame1_);
  //  std::cout << prediction << std::endl;
  EXPECT_EQ(prediction, "");
}
TEST(LanePredictorTest, turnPredictionTest2) {
  LanePredictor lp(right_Turn_frame);
  cv::Mat edgess = lp.edgeDetector(right_Turn_frame);
  cv::Mat roied = lp.roiMaskSelection(edgess);
  std::vector<std::vector<cv::Vec4i>> lanes(2);
  lanes = lp.houghTransform(roied);

  cv::Vec4d left{0, 0, 0, 0};
  cv::Vec4d right{0, 0, 0, 0};
  left = lp.lineFitting(lanes[0], right_Turn_frame);
  right = lp.lineFitting(lanes[1], right_Turn_frame);

  std::string prediction = lp.predictTurn(left, right, right_Turn_frame);
  //  std::cout << prediction << std::endl;
  EXPECT_EQ(prediction, "Right Turn Ahead!");
}

TEST(LanePredictorTest, turnPredictionTest3) {
  LanePredictor lp(left_Turn_frame);
  cv::Mat edgess = lp.edgeDetector(left_Turn_frame);
  cv::Mat roied = lp.roiMaskSelection(edgess);
  std::vector<std::vector<cv::Vec4i>> lanes(2);
  lanes = lp.houghTransform(roied);

  cv::Vec4d left{0, 0, 0, 0};
  cv::Vec4d right{0, 0, 0, 0};
  left = lp.lineFitting(lanes[0], left_Turn_frame);
  right = lp.lineFitting(lanes[1], left_Turn_frame);
  std::string prediction = lp.predictTurn(left, right, left_Turn_frame);
  //  std::cout << prediction << std::endl;
  EXPECT_EQ(prediction, "Left Turn Ahead!");
}
