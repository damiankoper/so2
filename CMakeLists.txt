# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required(VERSION 3.1)

project(MPK_Sim C CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)
# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Include Qt basic functions
include(QtCommon)
find_package(Qt5Widgets REQUIRED)

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
    src/Drawers/StopDrawer.cpp
    src/Drawers/RelationDrawer.cpp
    src/Drawers/VehicleDrawer.cpp
    src/Simulation/VehicleSimulator.cpp
    src/Simulation/Thread.cpp
)


add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES example.qrc src/Simulation/VehicleSimulator.cpp src/Simulation/VehicleSimulator.hpp src/Simulation/Thread.cpp src/Simulation/Thread.hpp src/Simulation/MpkSimulator.cpp src/Simulation/MpkSimulator.hpp src/Simulation/StopSimulator.cpp src/Simulation/StopSimulator.hpp src/Utils/RandUtils.cpp src/Utils/RandUtils.hpp)

# source_group("UI Files" FILES ${UI_FILES})

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

target_link_libraries (MPK_Sim ${CMAKE_THREAD_LIBS_INIT} Threads::Threads)


qt5_use_modules(${PROJECT_NAME} Widgets)
