cmake_minimum_required(VERSION 2.8)

project(compare_algos)

add_library(sort sort.h sort.cpp)
add_library(binsearch binsearch.h binsearch.cpp)

add_executable(main main.cpp)

target_link_libraries(binsearch sort)
target_link_libraries(main binsearch)