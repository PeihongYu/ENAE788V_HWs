cmake_minimum_required(VERSION 2.4.6)
project(RRT_search)
set(CMAKE_CXX_STANDARD 11)

add_executable(RRT RRT.cpp obstacle.h vector2d.h)