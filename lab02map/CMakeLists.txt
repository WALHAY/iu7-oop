cmake_minimum_required(VERSION 3.13)

project(lab02 VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g2")

file(GLOB SOURCES src/collection/*.cxx)
file(GLOB SSOURCES src/*.cxx)

add_executable(${PROJECT_NAME} ${SOURCES} ${SSOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    inc/
)


