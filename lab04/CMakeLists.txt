cmake_minimum_required(VERSION 3.21)

project(Elevator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(APP_NAME Elevator)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB SOURCES src/*.cxx)
file(GLOB HEADERS inc/*.hpp)

qt6_wrap_cpp(MOC_SOURCES ${HEADERS})  # Ensure moc runs on Door.hpp

include_directories(inc)

add_executable(Elevator ${MOC_SOURCES} ${SOURCES})

target_link_libraries(${APP_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
