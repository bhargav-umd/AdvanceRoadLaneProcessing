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
#include "../include/ReadAndDisplay.hpp"
/**
 * @brief      Main function that implements Lane Detection Pipeline
 * @Param[in]      None
 * @return     return 0
 */
int main() {
  ReadAndDisplay rd("../Dataset/Dataset2.mp4", "../Output/LaneDetector.avi");

  rd.display();
  return 0;
}
