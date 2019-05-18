cmake_minimum_required(VERSION 3.2.1)

FIND_PACKAGE( OpenCV REQUIRED )


add_executable(shell-app
                  main.cpp
                  LaneDetector.cpp 
	        	 LanePredictor.cpp)
target_link_libraries( shell-app ${OpenCV_LIBS})
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
