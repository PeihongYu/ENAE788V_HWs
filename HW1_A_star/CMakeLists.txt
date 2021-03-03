cmake_minimum_required(VERSION 2.4.6)
project(A_star_search)
set(CMAKE_CXX_STANDARD 11)

add_executable(run_simple_graph_search simple_graph_search.cpp ../HW2_RRT/RRT.cpp)