cmake_minimum_required(VERSION 3.1)
project(Lab6)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Task1 task1.cpp descriptor_methods.cpp matcher_methods.cpp)
target_link_libraries(Task1 ${OpenCV_LIBS})