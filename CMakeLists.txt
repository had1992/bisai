cmake_minimum_required(VERSION 3.6)
project(bisai)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp function.cpp Point.h IO.cpp)
add_executable(bisai ${SOURCE_FILES})