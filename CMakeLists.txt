cmake_minimum_required(VERSION 3.8)
project(Project5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES dlist.h calc.cpp)
add_executable(Project5 ${SOURCE_FILES})