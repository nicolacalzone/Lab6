cmake_minimum_required(VERSION 3.10)
project(Lab6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ~/workspace/opencv_build/opencv_contrib/modules)
set(OpenCV_DIR ~/workspace/opencv_build/opencv_contrib/build)

find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc imgcodecs xfeatures2d PATHS ~/workspace/opencv_build/opencv_contrib)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Task1 task1.cpp)

target_link_libraries(Task1 ${OpenCV_LIBS})