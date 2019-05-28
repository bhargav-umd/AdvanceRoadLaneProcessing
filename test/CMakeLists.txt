cmake_minimum_required(VERSION 2.6)
set(GTEST_SHUFFLE 1)
FIND_PACKAGE( OpenCV REQUIRED)

#FIND_PACKAGE(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_executable( cpp-test 
		main.cpp 
        LaneDetectorTest.cpp 
        LanePredictorTest.cpp
        ReadandDisplayTest.cpp 
        ../app/LaneDetector.cpp 
        ../app/LanePredictor.cpp
       ../app/ReadAndDisplay.cpp  

)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cpp-test PUBLIC gtest)
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS}) # ${GTEST_LIBRARIES}

include_directories(
    ${CMAKE_SOURCE_DIR}/include
 #   ${GTEST_INCLUDE_DIRS}
)
