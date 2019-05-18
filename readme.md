# Traffic Lane Detection
[![Build Status](https://travis-ci.com/bhargav-umd/AdvanceRoadLaneProcessing.svg?branch=master)](https://travis-ci.com/bhargav-umd/AdvanceRoadLaneProcessing)
[![Coverage Status](https://coveralls.io/repos/github/bhargav-umd/AdvanceRoadLaneProcessing/badge.svg?branch=master)](https://coveralls.io/github/bhargav-umd/AdvanceRoadLaneProcessing?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---

## Team Members
- Mayank Pathak
- Bhargav Dandamudi
## OverView

The aim of this project is to develop a Traffic Lane Detection algorithm. A specific Dataset has been chosen from the available online datasets. This dataset involves low light conditions, patchy road, no lane marking in few frames, and vehicle passing other vehicles using wrong lane. 

At this point of time, a lane detection algorithm is proposed. The project will use a video feed from Lane dataset as input to detect Lanes. It will also be able to predict any turns detected in the video frame. 

The project will be divided into 3 sprints, each for a time period of one week. Product backlog will be maintained for every sprint. Overall product requirements will be distributed
among sprints.

The project also detects if the vehicle is in the wrong lane, by detecting yellow lane coordinates and comparing it with predefined threshold. It shows the wrong lane indication if the vehicle is in wrong lane and shows to stay on lane if correct lane.
    The project uses th econcept of vanishing point to find if their is turn in near future.
There are two classes: LaneDetector and LanePredictor. Later is derivecd from the former class, inheriting all the functions.


## Approach

- Frames will be grabbed from the given dataset video and processed with smoothing filter. 
![inputImage](https://github.com/mayankpathak10/MidTerm_LaneDetection/blob/master/Outputs/Input%20Image%20Frame.png)
- Followed with HSV/RGB/Lab thresholding.
-  After applying an appropriate threshold, an edge detector would be used. To find lanes on the current frame Hough transform will be used.
![inputImage](https://github.com/mayankpathak10/MidTerm_LaneDetection/blob/master/Outputs/edged%20Image.png)
- Followed with selection of ROI.
![inputImage](https://github.com/mayankpathak10/MidTerm_LaneDetection/blob/master/Outputs/After%20Implementing%20Roi.png)
- Turns will be predicted by analyzing vanishing point and the slope of detected lanes. Respective lanes and predicted turn indicators will be plotted on the current frame.
![inputImage](https://github.com/mayankpathak10/MidTerm_LaneDetection/blob/master/Outputs/LeftTurn.png)
![inputImage](https://github.com/mayankpathak10/MidTerm_LaneDetection/blob/master/Outputs/RightTurn.png)
- Wrong lane indication will be shown based on yellow lane's location.
![inputImage](https://github.com/mayankpathak10/MidTerm_LaneDetection/blob/master/Outputs/WrongLane.png)
- Finally, test cases will be verified.

The UML Activity diagram for this approach is shown below:

![inputImage](https://github.com/mayankpathak10/MidTerm_LaneDetection/blob/master/UML/Revised/Revised_ActivityDiagram_Midterm.jpeg)

## Dependencies

The only dependency for this project is OpenCV 3.4.0. To install it, follow the next steps:

```
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
cd ~/<my_working_directory>
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j$(nproc)
sudo make install
sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
```

## How to Build and Run Demo

To build and run the demo, please follow the below steps:
- To build:
```
git clone https://github.com/mayankpathak10/MidTerm_LaneDetection.git
cd <path to repository>
mkdir Dataset
cd Dataset
Download Dataset Video from:"https://drive.google.com/file/d/1upkjKZvkz8Fwxey41YOMnNOI8oh51Jf5/view?usp=sharing"
cd ..
mkdir build
cd build
cmake ..
make
```
- Run the demo.
 ```
 ./app/shell-app
 ```
 ## How to run tests
```
./test/cpp-test
```

## Doxygen Documentation
To generate Doxygen Documentation in HTML and LaTEX, follow the next steps:
```
cd <path to repository>
mkdir <documentation_folder_name>
cd <documentation_folder_name>
doxygen -g <config_file_name>
```
Inside the configuration file, update:
```
PROJECT_NAME = 'your project name'
INPUT = ../LaneDetector ../include ../test
```
Run and generate the documents by running the next command:
```
doxygen <config_file_name>
```
To view the documents easily, access classLaneDetector.html, test_8cpp.html and demo_8cpp.html with your browser.

## Solo Iterative Process

SIP has been used to implement this project. A product backlog and Time log can be found the link below:

[![Packagist](https://img.shields.io/badge/SIP-Click%20Here-yellow.svg)] (https://docs.google.com/spreadsheets/d/1Xt0NCs74jCt25Va_o6To-D20YlPQTwmwj0yQRetGTwg/edit?usp=sharing)


The project consists of Two iterations:
Iteration 1: Design UML diagrams, Add product backlog, Collected Dataset, devise Lane detection Algorithm.

Driver: Mayank Pathak
Navigator: Bhargav Dandamudi

Iteration 2: Doxygen Documentation, Working Source Code, Finallized ReadMe file with clear instructions. Complete Backlogs.

Driver: Bhargav Dandamudi
Navigator: Mayank Pathak

## Software Technologies

Programming Language: Cpp
Compiler: Linux GCC
External Libraries: OpenCV
Version Control System: Git

## Deliverables

Source Code
Output Video

## Dataset:

Dataset for this project have been secured from Caltech Lanes and Oxford Lanes Dataset. Selected opensource datasets are included in the link below:
https://drive.google.com/open?id=1d4wX8wT0fDOeTtHd-jsBZRLYHG95-pC3

## Product Backlog 

The product 

```
git clone --recursive https://github.com/dpiet/cpp-boilerplate
cd <path to repository>
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```
