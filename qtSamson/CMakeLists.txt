project(qtSamson)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(qtSamson
        mainwindow.h
        mainwindow.cpp
	mainwindow.ui
        main.cpp)

include_directories(../samsonlib)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets samsonlib)
