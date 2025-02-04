cmake_minimum_required(VERSION 3.10)
project(CustomSTL)

add_subdirectory(vector)

add_executable(CustomSTL main.cc)

target_link_libraries(CustomSTL PRIVATE vector)
