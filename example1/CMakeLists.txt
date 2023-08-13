cmake_minimum_required(VERSION 3.5)
set(This example1)

project(${This} C CXX)

file(GLOB SOURCES "*.cpp" "*.h")

add_executable(${This} ${SOURCES})