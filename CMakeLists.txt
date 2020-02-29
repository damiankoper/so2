# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required(VERSION 3.0)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include Qt basic functions
include(QtCommon)

project(so2)

set(SOURCE_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/Geometry/Vector2i.cpp
    src/MPK/Stop.cpp
    src/MPK/Passenger.cpp
    src/MPK/Relation.cpp
    src/MPK/Vehicle.cpp
    src/MPK/MPKWorld.cpp
    src/RenderArea.cpp
)

add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES example.qrc)

find_package(Qt5Widgets REQUIRED)

# source_group("UI Files" FILES ${UI_FILES})

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

qt5_use_modules(${PROJECT_NAME} Widgets)
