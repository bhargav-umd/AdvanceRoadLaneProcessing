/**
MIT License

Copyright (c) 2018 Mayank Pathak, Bhargav Dandamudi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


 * @file    main.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This is the main file for the LaneDetection implementation.
 *  This program detects lanes from a given dataset video,
 *  predicts turns, and predicts if the vehicle is in wrong lane
 *  (based on Right-Hand Drive System).
 *
 * @dependencies: This program needs the following library files in
 *                order to execute properly.

 *   detectYellow.cpp   edgeDetector.cpp  houghTransform.cpp
 *   hsvThresholdY.cpp  lineFitting.cpp   plotPolygon.cpp
 *   predictTurn.cpp    readFrame.cpp     roiMaskSelection.cpp
 *   wrongLanePredictor.cpp               LaneDetector.hpp
 */

// Including defined header file
#include "../include/LaneDetector.hpp"
#include "../include/LanePredictor.hpp"
/**
 * @brief      Main function that implements Lane Detection Pipeline
 * @Param[in]      None
 * @return     return 0
 */
int main() {
  LaneDetector LaneDetector;   // Creating LaneDetector Object
  LanePredictor LanePredictor; // Creating LanePredictor Object
  // int total_frames;  // to store total number of frames
  cv::Vec4d last_lanes;   // to store last detected lanes
  cv::Vec4d last_l_lanes; // to store last detected Left lanes

  // Creating Video object for Input Video
  // to get frame height and width
  cv::VideoCapture frameCount("../Dataset/Dataset2.mp4");
  int frame_width = frameCount.get(CV_CAP_PROP_FRAME_WIDTH);
  int frame_height = frameCount.get(CV_CAP_PROP_FRAME_HEIGHT);

  // Creating Video Object for Output Video
  cv::VideoWriter video("../Output/LaneDetector.avi",
                        CV_FOURCC('M', 'J', 'P', 'G'), 10,
                        cv::Size(frame_width, frame_height));

  int total_frames = frameCount.get(CV_CAP_PROP_FRAME_COUNT);

  // looping over all the frames to process images,
  // detect lanes and, predict turns.
  for (int i = 1; i < total_frames; ++i) {
    // Printing the current frame index
    std::cout << "reading Frame: " << i << std::endl;
    // To read the image matrix from the current frame
    cv::Mat test_image = LaneDetector.readFrame(i);
    // Making copy of image for plotting output
    cv::Mat copy_test = test_image.clone();
    // Create vector to store right lane hough lines
    cv::Vec4d right_lanes;
    // Create vector to store left lane hough lines
    cv::Vec4d left_lanes;
    cv::Mat edged_image; // Create a matrix to store edges

    // To find edges in the image, using canny edge detector
    edged_image = LaneDetector.edgeDetector(test_image);
    // Cropping region of interest
    cv::Mat roi_image = LaneDetector.roiMaskSelection(edged_image);
    // detecting all valid hough lines
    std::vector<std::vector<cv::Vec4i>> all_lanes =
        LaneDetector.houghTransform(roi_image);
    // Condition to check if right lanes are detected
    // if not use the last detected lanes
    if (all_lanes[0].size() > 0) {
      right_lanes = LaneDetector.lineFitting(all_lanes[0], copy_test);
      last_lanes = right_lanes;
    } else {
      right_lanes = last_lanes;
    }

    // Condition to check if right lanes are detected
    // if not use the last detected lanes
    if (all_lanes[1].size() > 0) {
      left_lanes = LaneDetector.lineFitting(all_lanes[1], copy_test);
      last_l_lanes = left_lanes;
    } else {
      left_lanes = last_l_lanes;
    }

    //  Detecting yellow lanes location to predict correct lane
    cv::Vec4d yellow_lanes = LanePredictor.detectYellow(copy_test);
    //  plotting polygon over detected lanes
    cv::Mat output =
        LanePredictor.plotPolygon(copy_test, left_lanes, right_lanes);
    //  function to check lane using detected yellow lanes
    std::string laneIndicator = LanePredictor.wrongLanePredictor(yellow_lanes);
    //  display Lane status on output image frame
    if (laneIndicator == ("Wrong Lane!!")) {
      cv::putText(copy_test, laneIndicator, cv::Point(180, 200), // Coordinates
                  cv::FONT_HERSHEY_PLAIN,                        // Font
                  2,                                             // Scale. 2.0
                  cv::Scalar(0, 0, 255),                         // BGR Color
                  2);                                            // thickness
    } else {
      cv::putText(copy_test, laneIndicator, cv::Point(210, 430), // Coordinates
                  cv::FONT_HERSHEY_SIMPLEX,                      // Font
                  0.75,                                          // Scale. 2.0
                  cv::Scalar(102, 50, 0),                        // BGR Color
                  2);                                            // thickness
    }

    // predict turn and show it on image
    // copy_test =
    //     LanePredictor.predictTurn(left_lanes, right_lanes, copy_test);
    std::string turn_predict =
        LanePredictor.predictTurn(left_lanes, right_lanes, copy_test);

    //  display Lane status on output image frame
    if (turn_predict == "Left Turn Ahead!" ||
        turn_predict == "Right Turn Ahead!") {
      cv::putText(copy_test, turn_predict, cv::Point(243, 400), // Coordinates
                  cv::FONT_HERSHEY_PLAIN,                       // Font
                  1.25,                   // Scale. 2.0 = 2x bigger
                  cv::Scalar(102, 51, 0), // BGR Color
                  2);                     // thickness
    }
    // showing final output image
    cv::imshow("Frame", copy_test);
    // writing output video
    video.write(copy_test);
    cv::waitKey(0); // adding delay to show image
  }

  // When everything done, release the video capture and write object
  video.release();

  // Closes all the windows
  cv::destroyAllWindows();

  return 0;
}
