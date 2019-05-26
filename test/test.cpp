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
#include <gtest/gtest.h>

/**
 * @brief To test if the lanes are detected in the given
 * Frame.
 */
// std::string LaneTestingforTurn(int framenumber) {
//   LaneDetector LaneDetector;   // Creating LaneDetector Object
//   LanePredictor LanePredictor; // Creating LanePredictor Object
//
//   std::string predicted_turn;
//   // predicted_turn = "straight";
//   // Create vector to store right lane hough lines
//   cv::Vec4d right_lanes;
//   // Create vector to store left lane hough lines
//   cv::Vec4d left_lanes;
//   cv::Mat test_image = LaneDetector.readFrame(framenumber);
//   cv::Mat edged_image = LaneDetector.edgeDetector(test_image);
//   // Cropping region of interest
//   cv::Mat roi_image = LaneDetector.roiMaskSelection(edged_image);
//   // detecting all valid hough lines
//   std::vector<std::vector<cv::Vec4i>> all_lanes =
//       LaneDetector.houghTransform(roi_image);
//
//   // Condition to check if right lanes are detected
//   // if not use the last detected lanes
//   if (all_lanes[0].size() > 0) {
//     right_lanes = LaneDetector.lineFitting(all_lanes[0], test_image);
//   }
//
//   // Condition to check if right lanes are detected
//   // if not use the last detected lanes
//   if (all_lanes[1].size() > 0) {
//     left_lanes = LaneDetector.lineFitting(all_lanes[1], test_image);
//   }
//
//   predicted_turn =
//       LanePredictor.predictTurn(left_lanes, right_lanes, test_image);
//
//   return predicted_turn;
/* } */

/**
 * @brief To test if the lanes are detected in the given
 * Frame.
 */
/* int LaneTesting(int framenumber) { */
// LaneDetector LaneDetector;   // Creating LaneDetector Object
// LanePredictor LanePredictor; // Creating LanePredictor Object
//
// // Create vector to store right lane hough lines
// std::vector<cv::Vec4i> right_lanes;
// // Create vector to store left lane hough lines
// std::vector<cv::Vec4i> left_lanes;
// cv::Mat test_image = LaneDetector.readFrame(framenumber);
// cv::Mat edged_image = LaneDetector.edgeDetector(test_image);
// // Cropping region of interest
// cv::Mat roi_image = LaneDetector.roiMaskSelection(edged_image);
// // detecting all valid hough lines
// std::vector<std::vector<cv::Vec4i>> all_lnes =
//     LaneDetector.houghTransform(roi_image);
//
// // Condition to check if right lanes are detected
// // if not use the last detected lanes
// // cv::size_t = all_lnes[0].size;
//
// right_lanes = all_lnes[0];
// left_lanes = all_lnes[1];
// if (right_lanes.size() > 0 && left_lanes.size() > 0) {
//   int flag = 1;
//   return flag;
// } else {
//   int flag = 0;
//   return flag;
// }
//
// // return flag;
/* } */

/**
 *@brief Test case to test if lane is detected.
 */
/* TEST(LaneTest, lane_detected) { */
// int i = LaneTesting(10);
// EXPECT_EQ(i, 1);
/* } */

/**
 *@brief Test case to test if wrong lane detection is working.
 */
/* TEST(LaneTest, Lane_correct) { */
//   LanePredictor lp;
//   cv::Vec4d points(-596, 1124, 1083, -359);
//   EXPECT_EQ(lp.wrongLanePredictor(points), "Stay on this Lane!");
// }
//
/**
 *@brief Test case to test if wrong lane detection is working.
 */
// TEST(LaneTest, lane_wrong) {
//   LanePredictor lp;
//   cv::Vec4d points(120, -716, 556, 1481);
//   EXPECT_EQ(lp.wrongLanePredictor(points), "Wrong Lane!!");
/* } */

/**
 *@brief Test cases to test if lane is detected and if the lane is going
 *straight.
 */
/* TEST(LaneTest, no_turn) { */
//   std::string s = LaneTestingforTurn(5);
//   EXPECT_EQ(s, "");
// }
//
/**
 *@brief Test cases to test if lane is detected and if the lane is turning
 *right.
 */
// TEST(LaneTest, right_turn) {
//   std::string s = LaneTestingforTurn(178);
//   EXPECT_EQ(s, "Right Turn Ahead!");
// }
//
/**
 *@brief Test cases to test if lane is detected and if the lane is turning left.
 */
// TEST(LaneTest, left_turn) {
//   std::string s = LaneTestingforTurn(438);
//   EXPECT_EQ(s, "Left Turn Ahead!");
/* } */
