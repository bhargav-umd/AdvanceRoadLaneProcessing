#include "../include/LaneDetector.hpp"

/**
 * @brief      reads image and return lane points
 *             This file is a library file to implement hough tranform to find
 *             lines in the edged image then classify detected lines into left
 *             and right lane
 * @param[in]  roi_image cv::Mat
 */
std::vector<std::vector<cv::Vec4i>>
LaneDetector::houghTransform(cv::Mat roi_image) {
  // vector to store left and right lane points
  std::vector<std::vector<cv::Vec4i>> lanes(2);
  // variable to iterate over lines
  size_t iter_size = 0;
  // variable to store line end points
  cv::Point pnt1;
  cv::Point pnt2;
  // slope threshold to filter lines
  double slope_thresh = 0.3;
  std::vector<double> slopes;
  std::vector<cv::Vec4i> selected_lines;
  std::vector<cv::Vec4i> right_lines, left_lines;
  std::vector<cv::Vec4i> lines_p; // to store hough lines
  // center axis to classify left and right lanes
  double imgCenterY;
  imgCenterY = static_cast<double>((roi_image.cols / 2));
  // finding hough lines
  cv::HoughLinesP(roi_image, lines_p, 1, CV_PI / 180, 20, 20, 30); // HoughP
  cv::Mat cdst = roi_image.clone();
  // Calculate the slope of all the detected lines
  // std::cout << lines_p.size() << ":lines number" << std::endl;

  for (auto i : lines_p) {
    pnt1 = cv::Point(i[0], i[1]);
    pnt2 = cv::Point(i[2], i[3]);
    cv::line(cdst, pnt1, pnt2, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);

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
  //  cv::imshow("lines", cdst);
  // Split the lines into right and left lines
  imgCenterY = static_cast<double>((roi_image.cols / 2));
  // std::cout << imgCenterY << ":center y" << std::endl;
  while (iter_size < selected_lines.size()) {
    pnt1 =
        cv::Point(selected_lines[iter_size][0], selected_lines[iter_size][1]);
    pnt2 =
        cv::Point(selected_lines[iter_size][2], selected_lines[iter_size][3]);

    // Condition to classify line as left side or right side

    if (slopes[iter_size] > 0 && pnt2.x > imgCenterY && pnt1.x > imgCenterY) {
      /*    std::cout << " right: pnt 1 x : " <<
       * selected_lines[iter_size][0] */
      //
      // << ", right pnt 1 y: " << selected_lines[iter_size][1]
      // << ", right pnt 2 x: " << selected_lines[iter_size][2]
      // << ", right pnt 2 y: " << selected_lines[iter_size][3]
      /* << std::endl; */

      right_lines.push_back(selected_lines[iter_size]);
      right_lines.push_back(selected_lines[iter_size]);
    } else if (slopes[iter_size] < 0 && pnt2.x < imgCenterY &&
               pnt1.x < imgCenterY) {
      /*       std::cout << "left: pnt 1 x, " <<
       * selected_lines[iter_size][0] */
      //
      // << "left pnt 1 y, " << selected_lines[iter_size][1]
      // << "left pnt 2 x, " << selected_lines[iter_size][2]
      // << "left  pnt 2 y, " << selected_lines[iter_size][3]
      /* << std::endl; */

      left_lines.push_back(selected_lines[iter_size]);
    }
    iter_size++;
  }

  // storing left and righ lane points in an array
  lanes[0] = right_lines;
  lanes[1] = left_lines;
  // std::cout << lanes[0].size() << ": right size" << std::endl;
  // std::cout << lanes[1].size() << ": left size" << std::endl;
  return lanes;
}

cv::Mat LaneDetector::roiMaskSelection(cv::Mat hsv_threshold) {
  // std::cout << hsv_threshold.cols << ": input col size " << std::endl;
  cv::Mat roi; // Matrix to save image
  // creating empty mask image
  cv::Mat mask = cv::Mat::zeros(hsv_threshold.size(), hsv_threshold.type());
  // determining polygon vertices for roi
  cv::Point pts[4] = {cv::Point(73, 441), cv::Point(254, 341),
                      cv::Point(357, 341), cv::Point(500, 441)};
  // Create a binary polygon mask
  cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 255, 255));
  // Multiply the edges image and the mask to get the output
  cv::bitwise_and(hsv_threshold, mask, roi);
  cv::imwrite("../Output/roitest.jpg", roi);
  return roi;
}

/**
 * @brief      reads image and applys canny edge detecting.
 *             This file is a library file to implement Canny edge detection
 *             algorithm on the input frame. The kernel size for the edge
 *             detection algorithm is chosen as 3.
 * @param[in]  roi_image  cv::Mat
 * @return     edge_image cv::Mat
 */
cv::Mat LaneDetector::edgeDetector(cv::Mat roi_image) {
  cv::Mat edge, edge_image;
  // cv::Canny(roi_image, edge, 0, 255, 3);
  cv::Canny(roi_image, edge, 50, 200, 3);
  edge.convertTo(edge_image, CV_8U);
  // cv::imshow("edge_Image", edge_image);
  // cv::imwrite("../Output/edge_image.jpg", edge_image);
  return edge_image;
}

/**
 * @brief      fits a line over given input points
 *              This file is a library file to fit lines over the
 *             detected lines on the input image.
 * @param[in]  lineVector  The line vector
 * @param[in]  inputImage  The input image
 *
 * @return     { return two points based one fit line}
 */
cv::Vec4d LaneDetector::lineFitting(std::vector<cv::Vec4i> lineVector,
                                    cv::Mat inputImage) {
  std::vector<cv::Point> all_points; // to store all points in a vector
  cv::Vec4d fit_line;                // to  store output of the function
  cv::Point pt1, pt2;                // end points of the fit line
  // looping over total number lines
  for (auto i : lineVector) {
    cv::Point initial_point = cv::Point(i[0], i[1]);
    cv::Point final_point = cv::Point(i[2], i[3]);

    all_points.push_back(initial_point);
    all_points.push_back(final_point);
  }
  // open cv function to fitline of all the segregated points
  cv::fitLine(all_points, fit_line, CV_DIST_L2, 0, 0.01, 0.01);

  // calculating initial and final points of the lines
  double d = sqrt(static_cast<double>(fit_line[0] * fit_line[0]) +
                  static_cast<double>(fit_line[1] * fit_line[1]));
  fit_line[0] /= d;
  fit_line[1] /= d;
  float t = (inputImage.cols + inputImage.rows);
  pt1.x = cvRound(fit_line[2] - fit_line[0] * t);
  pt1.y = cvRound(fit_line[3] - fit_line[1] * t);
  pt2.x = cvRound(fit_line[2] + fit_line[0] * t);
  pt2.y = cvRound(fit_line[3] + fit_line[1] * t);

  // storign all points in one array
  fit_line[0] = pt1.x;
  fit_line[1] = pt1.y;
  fit_line[2] = pt2.x;
  fit_line[3] = pt2.y;
  /*   std::cout << fit_line[0] << " pt1.x" << std::endl; */
  // std::cout << fit_line[1] << " pt1.y" << std::endl;
  //
  // std::cout << fit_line[2] << " pt2.x" << std::endl;
  //
  // std::cout << fit_line[3] << " pt2.y" << std::endl;
  /*  */
  return fit_line;
}
