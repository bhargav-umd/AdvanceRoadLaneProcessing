#include "LaneDetector.hpp"
#include "LanePredictor.hpp"
#include <iostream>
#include <string>

#ifndef INCLUDE_READANDDISPLAY_H_
#define INCLUDE_READANDDISPLAY_H_

class ReadAndDisplay {
private:
  std::string input_add, output_add;
  int frame_width, frame_height, total_frames;
  cv::Mat image, copy_image, edge_image, roi_image;
  /* static cv::Vec4d right_lanes; */
  // cv::Vec4d left_lanes;
  // cv::Vec4d last_lanes; // to store last detected lanes
  // cv::Vec4d last_l_lanes;
  // cv::Vec4d yellow_lanes;
  cv::Mat polygon_image;

public:
  static cv::Vec4d right_lanes;
  static cv::Vec4d left_lanes;
  static cv::Vec4d last_lanes; // to store last detected lanes
  static cv::Vec4d last_l_lanes;
  static cv::Vec4d yellow_lanes;
  static std::vector<std::vector<cv::Vec4i>> all_lanes;
  ReadAndDisplay(std::string input_address, std::string output_address) {
    this->input_add = input_address;
    this->output_add = output_address;
  }
  /*
   * @brief      Reads a frame.
   *
   * @param[in]  frame_number  The frame number
   *
   * @return     { frame of the given frame index}
   */
  void readFrame(int frame_number);
  void read();
  void processDetectionImages(int i);
  void plotPolygon();
  void laneIndicatorImage();
  void display();
  int getFrameWidth();
  int getFrameHeight();
  cv::Mat getPolygonImage();
};
/* cv::Vec4d ReadAndDisplay::right_lanes{0, 0, 0, 0}; */
// cv::Vec4d ReadAndDisplay::left_lanes{0, 0, 0, 0};
// cv::Vec4d ReadAndDisplay::last_lanes{0, 0, 0, 0};
// // to store last detected lanes
// cv::Vec4d ReadAndDisplay::last_l_lanes{0, 0, 0, 0};
// cv::Vec4d ReadAndDisplay::yellow_lanes{0, 0, 0, 0};
//   std::vector<std::vector<cv::Vec4i>> ReadAndDisplay::all_lanes;
/*  */
#endif
