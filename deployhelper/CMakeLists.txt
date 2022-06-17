cmake_minimum_required(VERSION 3.14)

project(lqtEmpty LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE MinSizeRel)

string(REGEX REPLACE "/[Oo][A-Za-z0-9]" "/Od" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Qt5 REQUIRED COMPONENTS
  Core
  Gui
  Network
  OpenGL
  Positioning
  PrintSupport
  Qml
  Quick
  QuickWidgets
  Sql
  Test
  UiTools
  WebChannel
  WebEngineCore
  WebEngineWidgets
  WebSockets
  Widgets
)

add_executable(lqtEmpty main.cpp)
target_link_libraries(lqtEmpty 
  Qt5::Core
  Qt5::Gui
  Qt5::Network
  Qt5::OpenGL
  Qt5::Positioning
  Qt5::PrintSupport
  Qt5::Qml
  Qt5::Quick
  Qt5::QuickWidgets
  Qt5::Sql
  Qt5::Test
  Qt5::UiTools
  Qt5::WebChannel
  Qt5::WebEngineCore
  Qt5::WebEngineWidgets
  Qt5::WebSockets
  Qt5::Widgets
)
