/**
 * @file    test.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This is the header file to declare all the class variables and
 *  functions that will be used for the Lane Detection Implementation.
 *
 * @dependencies: This program needs the following libraries in
 *                order to execute properly:
 *                OpenCV, String, IOstream, vector
 */

#include "../include/LaneDetector.hpp"
#include "../include/LanePredictor.hpp"
#include "../include/ReadAndDisplay.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat testImage = cv::imread("../data/edge_image.jpg");
cv::Mat roied = cv::imread("../data/roitest.jpg");
cv::Mat frame_ = cv::imread("../data/test.jpg");
LaneDetector ld_object(testImage);
cv::Mat edgess = ld_object.edgeDetector(testImage);
cv::Mat roied_edges = ld_object.roiMaskSelection(testImage);

TEST(LaneDetectorTest, roiMaskSelection) {
  cv::Mat roiImage = ld_object.roiMaskSelection(testImage);
  cv::Mat roiImage_test = testImage;
  cv::Mat diff;
  // cv::imshow("roiImage", roiImage);
  // cv::imshow("roied", roied);
  //  cv::waitKey(0);
  cv::bitwise_xor(roiImage, roied, diff);
  cv::cvtColor(diff, diff, CV_BGR2GRAY);
  ASSERT_EQ(cv::countNonZero(diff), 48);
}

TEST(LaneDetectorTest, edgesTest) {
  cv::Mat edge_test = ld_object.edgeDetector(frame_);
  cv::Mat result1, result2, r3;
  result1 = cv::imread("../data/test.jpg");
  cv::Canny(result1, result2, 50, 200, 3);
  result2.convertTo(r3, CV_8U);
  // cv::imshow("r3", r3);
  // cv::imshow("edges", edge_test);
  cv::Mat diff;
  cv::bitwise_xor(edge_test, r3, diff);
  ASSERT_EQ(cv::countNonZero(diff), 0);
}
//
TEST(LaneDetectorTest, houghTest) {
  std::vector<std::vector<cv::Vec4i>> lanes(2);
  cv::Mat frame_ = cv::imread("../data/test.jpg");
  LaneDetector ld(frame_);
  cv::Mat edgess = ld.edgeDetector(frame_);
  cv::Mat roied = ld.roiMaskSelection(edgess);
  lanes = ld_object.houghTransform(roied);
  EXPECT_EQ(int(lanes[0].size()), 12);
  EXPECT_EQ(int(lanes[1].size()), 8);
  EXPECT_EQ(lanes[0][0][0], 331);
  EXPECT_EQ(lanes[0][0][1], 351);
  EXPECT_EQ(lanes[0][0][2], 448);
  EXPECT_EQ(lanes[0][0][3], 433);

  EXPECT_EQ(lanes[1][0][0], 149);
  EXPECT_EQ(lanes[1][0][1], 441);
  EXPECT_EQ(lanes[1][0][2], 265);
  EXPECT_EQ(lanes[1][0][3], 360);
}

TEST(LaneDetectorTest, fittingTest) {
  cv::Vec4d line;
  std::vector<std::vector<cv::Vec4i>> lanes(2);
  LaneDetector ld(frame_);
  cv::Mat edgess = ld.edgeDetector(frame_);
  cv::Mat roied = ld.roiMaskSelection(edgess);
  lanes = ld_object.houghTransform(roied);
  line = ld_object.lineFitting(lanes[0], frame_);
  EXPECT_EQ(line[0], -516);
  EXPECT_EQ(line[1], -226);
  EXPECT_EQ(line[2], 1337);
  EXPECT_EQ(line[3], 1032);
  line = ld_object.lineFitting(lanes[1], frame_);
  EXPECT_EQ(line[0], -694);
  EXPECT_EQ(line[1], 1062);
  EXPECT_EQ(line[2], 1112);
  EXPECT_EQ(line[3], -263);
}
