cmake_minimum_required(VERSION 3.21)

project(WireframeViewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(APP_NAME WireframeViewer)

if (UNIX)
	add_compile_options(-mno-direct-extern-access)
endif (UNIX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB_RECURSE SOURCES src/*.cxx)
file(GLOB_RECURSE HEADERS inc/*.hpp)

qt6_wrap_cpp(MOC_SOURCES ${HEADERS})  # Ensure moc runs on Door.hpp

include_directories(inc)

add_executable(WireframeViewer ${MOC_SOURCES} ${SOURCES})

target_link_libraries(${APP_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
