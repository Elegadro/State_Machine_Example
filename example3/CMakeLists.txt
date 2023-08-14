cmake_minimum_required(VERSION 3.5)
set(This example3)

project(${This} C CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES "*.cpp" "*.h")

add_executable(${This} ${SOURCES})

target_link_libraries(${This} ${OpenCV_LIBS})