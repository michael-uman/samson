project(qmlSamson)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)


add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})

qt5_add_resources(QT_RESOURCES qml.qrc)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS})
include_directories(../samsonlib)

add_executable(qmlSamson
        main.qml
        appobject.cpp
        main.cpp ${QT_RESOURCES})
        
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Qml Qt5::Quick samsonlib)


