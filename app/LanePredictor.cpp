#include "../include/LanePredictor.hpp"
#include "../include/LaneDetector.hpp"
/**
 * @brief   [LanePredictor::wrongLanePredictor description]
 *          This file is a library file to predict vehicle position
 *          based on yellow lane w.r.t. the frame size.
 *          (Assuming Right-Hand Drive System)
 * @param[in]  yellow_line     [cv::Vec4d]
 * @return lane_indicator  [string]
 */
std::string LanePredictor::wrongLanePredictor(cv::Vec4d yellow_line) {
  cv::Vec4d yellow_lanes;
  cv::Vec4d white_lanes;
  // yellow lane y reference coordinate
  double ylower = 460;
  std::string lane_indicator = "No Lane Found :/";
  double x11 = yellow_line[0];
  double y11 = yellow_line[1];
  double x21 = yellow_line[2];
  double y21 = yellow_line[3];
  double slope1 = ((y21 - y11) / (x21 - x11));
  // to store x coordinate of yellow lane
  cv::Point lower_yellow;
  // to calculate x coordinate for the lower
  // y reference coordinate of yellow lane
  lower_yellow.x = x11 + (ylower - y11) / slope1;

  // applying threshold to determine lane
  if (lower_yellow.x > 320) {
    std::string lane_indicator = "Wrong Lane!!";
    return lane_indicator;
  } else {
    std::string lane_indicator = "Stay on this Lane!";
    return lane_indicator;
  }

  return lane_indicator;
}

/**
 * @brief           LanePredictor::detectYellow,
 *                  returns end points of yellow lanes
 *                  after curve fitting on points found from hough transform.
 *                  This file is a library file to detect yellow lanes as per
 *                  hsvthreshold output. This file inherits hsvThresholdY,
 *                  edgeDetector, roiMaskSelection and lineFitting functions
 *                  from LaneDetector Class
 * @param[in]  frame [cv::Mat]
 * @return       [cv::Vect4d]
 */
cv::Vec4d LanePredictor::detectYellow(cv::Mat frame) {
  cv::Mat copy_fame; // to store input image copy
  frame.copyTo(copy_fame);
  cv::Point pnt1;
  cv::Point pnt2;
  cv::Vec4d yellow_lanes;
  double slope_thresh = 0.7;
  std::vector<double> slopes;
  std::vector<cv::Vec4i> lines_p;
  std::vector<cv::Vec4i> selected_lines;

  cv::Mat hsvThresholdImage = LanePredictor::hsvThresholdY(frame);
  cv::Mat edgesP = LanePredictor::edgeDetector(hsvThresholdImage);
  cv::Mat roiP = LanePredictor::roiMaskSelection(edgesP);

  // finding hough lines from the edges found on the image
  // values of parameters found using trial and error.
  HoughLinesP(roiP,        // Source Image
              lines_p,     // output lines
              1,           // rho
              CV_PI / 180, // theta
              10,          // threshold of intersections
              10,          // min Line Lengths
              10);         // max gap between two points

  // extracting points from all the detected lines
  for (auto i : lines_p) {
    pnt1 = cv::Point(i[0], i[1]); // Point 1 of line vector
    pnt2 = cv::Point(i[2], i[3]); // Point 2 of line vector

    // Calculating Slope
    double slope =
        (static_cast<double>(pnt2.y) - static_cast<double>(pnt1.y)) /
        (static_cast<double>(pnt2.x) - static_cast<double>(pnt1.x) + 0.00001);

    // filtering lines as per the slope and
    // storing the selected lines and slopes
    if (std::abs(slope) > slope_thresh) {
      slopes.push_back(slope);
      selected_lines.push_back(i);
    }
  }

  // To fit line only if selected any
  if (selected_lines.size() > 0) {
    yellow_lanes = LanePredictor::lineFitting(selected_lines, copy_fame);
  }

  return yellow_lanes;
}
/**
 * @brief  LanePredictor::hsvThresholdY
 *         Split BGR image into HSV planes and apply threshold
 *         on each plane to detect Yellow Lanes.
 *
 * @param[in]  frame [cv::Mat]
 * @return threshold_image [cv::Mat]
 */
cv::Mat LanePredictor::hsvThresholdY(cv::Mat frame) {
  cv::Mat hsv, threshold_image;
  cv::Scalar hsv_low_y(1, 40, 133);
  cv::Scalar hsv_high_y(90, 150, 255);
  // convert RGB roiImage to hsv
  cv::cvtColor(frame, hsv, CV_BGR2HSV);
  std::vector<cv::Mat> hsv_planes;
  cv::split(hsv, hsv_planes);
  cv::Mat h = hsv_planes[0]; // H channel
  cv::Mat s = hsv_planes[1]; // S channel
  cv::Mat v = hsv_planes[2]; // V channel

  //// yellow color range, found by trial and error

  cv::inRange(hsv, hsv_low_y, hsv_high_y, threshold_image);

  return threshold_image;
}

/**
 * @file    plotPolygon.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to plot a polygon over
 *  detected lanes on the output frame.
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

/**
 * @brief      LanePredictor::plotPolygon
 *             This file is a library file to plot a polygon over
 *             detected lanes on the output frame.
 *
 * @param[in]  input_image  [cv::Mat]
 * @param[in]  yellow_lanes [cv::Vec4d]
 * @param[in]  white_lanes  [cv::Vec4d]
 * @return     output      [cv::Mat]
 */
cv::Mat LanePredictor::plotPolygon(cv::Mat input_image, cv::Vec4d yellow_lanes,
                                   cv::Vec4d white_lanes) {
  cv::Mat output;
  input_image.copyTo(output);
  cv::Point upper_yellow;
  cv::Point lower_yellow;
  cv::Point upper_white;
  cv::Point lower_white;
  double ylower = 480; // horizontal lower side of polygon
  double yupper = 360; // horizontal upper side of polygon
  // Splitting points from yellow lane
  double x11 = yellow_lanes[0];
  double y11 = yellow_lanes[1];
  double x21 = yellow_lanes[2];
  double y21 = yellow_lanes[3];
  double slope1 = ((y21 - y11) / (x21 - x11));
  // Splitting points from white lane
  double x12 = white_lanes[0];
  double y12 = white_lanes[1];
  double x22 = white_lanes[2];
  double y22 = white_lanes[3];
  double slope2 = ((y22 - y12) / (x22 - x12));

  // setting upper and lower y coordinate limits
  upper_white.y = upper_yellow.y = yupper;
  lower_white.y = lower_yellow.y = ylower;

  // calculating x coordinates for the polygon edges
  upper_yellow.x = x11 + (yupper - y11) / slope1;
  lower_yellow.x = x11 + (ylower - y11) / slope1;
  upper_white.x = x12 + (yupper - y12) / slope2;
  lower_white.x = x12 + (ylower - y12) / slope2;

  // Storing all points as vector, for plotting
  cv::Point pts[4] = {lower_yellow, upper_yellow, upper_white, lower_white};
  // drawing polygon using in-built opencv function
  cv::fillConvexPoly(output,                // output image
                     pts,                   // vertices
                     4,                     // number of vertices
                     cv::Scalar(0, 0, 255), // color of polygon
                     CV_AA);                // Anti-Aliasing

  // plotting polygon boundary lines
  line(input_image, lower_yellow, upper_yellow, cv::Scalar(25, 0, 51), 2,
       CV_AA);
  line(input_image, lower_white, upper_white, cv::Scalar(25, 0, 51), 2, CV_AA);
  line(input_image, upper_yellow, upper_white, cv::Scalar(25, 0, 51), 2, CV_AA);
  // adding transparency to the polygon
  cv::addWeighted(output, 0.3, input_image, 1.0 - 0.3, 0, input_image);

  return output;
}

/**
 * @brief   [LanePredictor::predictTurn]
 *          This file is a library file to predict turns based on the
 *          concept of vanishing point.
 *
 * @param[in]   left_lines  [cv::Vec4d]
 * @param[in]   right_lines [cv::Vec4d]
 * @param[in]   input_image [cv::Mat]
 * @return[in]  input_image [cv::Mat]
 */
std::string LanePredictor::predictTurn(cv::Vec4d left_lines,
                                       cv::Vec4d right_lines,
                                       cv::Mat input_image) {
  // finding intersection point between to lanes.
  cv::Point vanishingPoint;
  // extracting points from left_lines
  double x11 = left_lines[0];
  double y11 = left_lines[1];
  double x21 = left_lines[2];
  double y21 = left_lines[3];
  double slope1 = ((y21 - y11) / (x21 - x11));
  // extracting points from right_lines
  double x12 = right_lines[0];
  double y12 = right_lines[1];
  double x22 = right_lines[2];
  double y22 = right_lines[3];
  double slope2 = ((y22 - y12) / (x22 - x12));

  vanishingPoint.x =
      ((y22 - y11) + slope1 * x11 - slope2 * x22) / (slope1 - slope2);
  vanishingPoint.y =
      (slope1 * ((y22 - y11) - (slope2 * x22) + (slope2 * x11))) /
          (slope1 - slope2) +
      y11;

  // plotting vanishing point
  circle(input_image, vanishingPoint, 1, cv::Scalar(0, 255, 0), 3, 8, 0);

  // Thresholding to predict turns
  if (vanishingPoint.x < 287) {
    std::string turn_predict = "Left Turn Ahead!";

    return turn_predict;
  } else if (vanishingPoint.x > 317) {
    std::string turn_predict = "Right Turn Ahead!";

    return turn_predict;
  }

  return turn_predict;
}
