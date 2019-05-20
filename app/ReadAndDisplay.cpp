#include "../include/ReadAndDisplay.hpp"
#include "../include/LaneDetector.hpp"
#include "../include/LanePredictor.hpp"

/**
 * @brief  [LaneDetector::readFrame]
 *          This file is a library file to read image frames
 *          from the input image as per the frame number given
 *          as argument.
 *
 * @param[in]  frame_number [int]
 * @return frame        [cv::Mat]
 */
void ReadAndDisplay::readFrame(int frame_number) {
  cv::Mat frame; // matrix to store input frame
  // Video Object to read frame
  cv::VideoCapture cap(this->input_add);
  cap.set(cv::CAP_PROP_POS_FRAMES, frame_number);
  cap >> frame;
  this->image = frame;
}
void ReadAndDisplay::read() {
  cv::VideoCapture frameCount(this->input_add);
  this->frame_width = frameCount.get(CV_CAP_PROP_FRAME_WIDTH);
  this->frame_height = frameCount.get(CV_CAP_PROP_FRAME_HEIGHT);
  this->total_frames = frameCount.get(CV_CAP_PROP_FRAME_COUNT);
}

void ReadAndDisplay::processDetectionImages(int i) {
  //  for (int i = 1; i < this->total_frames; ++i) {
  // read();
  readFrame(i);
  this->copy_image = this->image.clone();
  LaneDetector ld(this->image);
  this->edge_image = ld.edgeDetector(this->image);
  this->roi_image = ld.roiMaskSelection(this->edge_image);
  std::vector<std::vector<cv::Vec4i>> all_lanes = ld.houghTransform(roi_image);
  // Condition to check if right lanes are detected
  // if not use the last detected lanes
  if (all_lanes[0].size() > 0) {
    right_lanes = ld.lineFitting(all_lanes[0], this->copy_image);
    this->last_lanes = right_lanes;
  } else {
    right_lanes = this->last_lanes;
  }

  // Condition to check if right lanes are detected
  // if not use the last detected lanes
  if (all_lanes[1].size() > 0) {
    left_lanes = ld.lineFitting(all_lanes[1], copy_image);
    this->last_l_lanes = this->left_lanes;
  } else {
    this->left_lanes = this->last_l_lanes;
  }
  LanePredictor lp(this->copy_image);
  this->yellow_lanes = lp.detectYellow();
}

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
/* void ReadAndDisplay::plotPolygon(cv::Mat input_image, cv::Vec4d yellow_lanes,
 */
// cv::Vec4d white_lanes) {
/*    */
void ReadAndDisplay::plotPolygon() {
  cv::Mat output;
  this->image.copyTo(output);
  cv::Point upper_yellow;
  cv::Point lower_yellow;
  cv::Point upper_white;
  cv::Point lower_white;
  double ylower = 480; // horizontal lower side of polygon
  double yupper = 360; // horizontal upper side of polygon
  // Splitting points from yellow lane
  double x11 = this->yellow_lanes[0];
  double y11 = this->yellow_lanes[1];
  double x21 = this->yellow_lanes[2];
  double y21 = this->yellow_lanes[3];
  double slope1 = ((y21 - y11) / (x21 - x11));
  // Splitting points from white lane
  double x12 = this->right_lanes[0];
  double y12 = this->right_lanes[1];
  double x22 = this->right_lanes[2];
  double y22 = this->right_lanes[3];
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
  line(this->copy_image, lower_yellow, upper_yellow, cv::Scalar(25, 0, 51), 2,
       CV_AA);
  line(this->copy_image, lower_white, upper_white, cv::Scalar(25, 0, 51), 2,
       CV_AA);
  line(this->copy_image, upper_yellow, upper_white, cv::Scalar(25, 0, 51), 2,
       CV_AA);
  // adding transparency to the polygon
  cv::addWeighted(this->copy_image, 0.3, this->copy_image, 1.0 - 0.3, 0,
                  this->copy_image);

  this->polygon_image = output;
}

void ReadAndDisplay::laneIndicatorImage() {
  LanePredictor lp(this->copy_image);
  std::string laneIndicator = lp.wrongLanePredictor(this->yellow_lanes);
  //  display Lane status on output image frame
  if (laneIndicator == ("Wrong Lane!!")) {
    cv::putText(this->copy_image, laneIndicator,
                cv::Point(180, 200),    // Coordinates
                cv::FONT_HERSHEY_PLAIN, // Font
                2,                      // Scale. 2.0
                cv::Scalar(0, 0, 255),  // BGR Color
                2);                     // thickness
  } else {
    cv::putText(this->copy_image, laneIndicator,
                cv::Point(210, 430),      // Coordinates
                cv::FONT_HERSHEY_SIMPLEX, // Font
                0.75,                     // Scale. 2.0
                cv::Scalar(102, 50, 0),   // BGR Color
                2);                       // thickness
  }

  // predict turn and show it on image
  // copy_test =
  //     LanePredictor.predictTurn(left_lanes, right_lanes, copy_test);
  std::string turn_predict =
      lp.predictTurn(left_lanes, right_lanes, copy_image);

  //  display Lane status on output image frame
  if (turn_predict == "Left Turn Ahead!" ||
      turn_predict == "Right Turn Ahead!") {
    cv::putText(copy_image, turn_predict, cv::Point(243, 400), // Coordinates
                cv::FONT_HERSHEY_PLAIN,                        // Font
                1.25,                   // Scale. 2.0 = 2x bigger
                cv::Scalar(102, 51, 0), // BGR Color
                2);                     // thickness
  }
}

void ReadAndDisplay::display() {
  read();
  cv::VideoWriter video(this->output_add, CV_FOURCC('M', 'J', 'P', 'G'), 10,
                        cv::Size(this->frame_width, this->frame_height));

  for (int i = 300; i < this->total_frames; ++i) {
    processDetectionImages(i);
    cv::imshow("detection images", this->copy_image);
    plotPolygon();
    cv::imshow("polygon", this->copy_image);
    laneIndicatorImage();
    cv::imshow("lanes", this->copy_image);
    cv::imshow("Frame", this->copy_image);

    video.write(this->copy_image);

    cv::waitKey(0);
  }
  video.release();
  cv::destroyAllWindows();
}
