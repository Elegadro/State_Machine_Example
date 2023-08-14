cmake_minimum_required(VERSION 3.5)
set(This example2)

project(${This} C CXX)

file(GLOB SOURCES "*.cpp" "*.h")

add_executable(${This} ${SOURCES})