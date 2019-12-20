project(samson)

set(CMAKE_CXX_STANDARD 14)
include_directories(../samsonlib)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} samsonlib)
