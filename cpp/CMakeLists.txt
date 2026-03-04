cmake_minimum_required(VERSION 3.5)
project(FullscreenWebViewer)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt6 COMPONENTS Widgets WebEngineWidgets REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)
