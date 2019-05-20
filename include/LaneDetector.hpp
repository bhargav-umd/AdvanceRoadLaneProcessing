/**
 * @file    main.cpp
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

#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <vector>

/**
 * @brief      Class for lane detector.Carries all the functions
 *             related to detect the yellow and white lanes
 */
class LaneDetector {
private:
  cv::Mat input_image; // variable to store the frame
  cv::Mat roi_image;
  cv::Mat gray_image;
  cv::Mat test_image;
  cv::Mat edged_image;
  cv::Mat thresh_image;
  std::vector<int> lines; // store all hough lines
  double rho = 1;         // hough transform parameter
  double theta = 1;       // hough transform parameter
  double threshold;
  double left_slope;
  double right_slope;
  double left_points;
  double right_points;

public:
  LaneDetector() { ; }
  LaneDetector(cv::Mat image) { this->input_image = image; };

  // Default constructor
  // ~LaneDetector(); // Default Destructor
  /**
   * @brief      Reads a frame.
   *
   * @param[in]  frame_number  The frame number
   *
   * @return     { frame of the given frame index}
   */
  //  cv::Mat readFrame(int frame_number);

  /**
   * @brief      { selects a trapezoidal region in given image}
   *
   * @param[in]  input_image  The input image
   *
   * @return     { retuns region of interest in given image }
   */
  cv::Mat roiMaskSelection(cv::Mat input_image);

  /**
   * @brief      { applies canny edge detections on given image }
   *
   * @param[in]  thresh_image  The thresh image
   *
   * @return     { image containing all the edges }
   */
  cv::Mat edgeDetector(cv::Mat thresh_image);

  /**
   * @brief      { Applies Hough Transform and classifies lanes
   *                based on slopes     }
   *
   * @param[in]  { cv::Mat edged Image }
   *
   * @return     { vector containing all points of
   *               left and right lanes }
   */
  std::vector<std::vector<cv::Vec4i>> houghTransform(cv::Mat);

  /**
   * @brief      { curve fits a line using multiple lines }
   *
   * @param[in] lines   {vector containing lines }
   * @param[in] cv::Mat { input_image }
   *
   * @return     { two ends of the fit line }
   */
  cv::Vec4d lineFitting(std::vector<cv::Vec4i>, cv::Mat);
};
