cmake_minimum_required(VERSION 2.8)

project(sort)

add_library(sort sort.h sort.cpp)

add_executable(main main.cpp)

target_link_libraries(main sort)