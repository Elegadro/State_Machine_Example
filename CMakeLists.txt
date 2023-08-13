cmake_minimum_required(VERSION 3.5)
set(This src)

file(GLOB SOURCES "*.cpp" "*.h")

add_executable(${This} ${SOURCES})