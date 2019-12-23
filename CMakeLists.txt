cmake_minimum_required(VERSION 3.15)
project(samson)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(samsonlib)
add_subdirectory(examples)
#include_directories(samsonlib)
#add_executable(${PROJECT_NAME} main.cpp)
#target_link_libraries(${PROJECT_NAME} samsonlib)
