cmake_minimum_required(VERSION 3.13)

project(lab02 VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES src/**/*.cxx)
file(GLOB SSOURCES src/*.cxx)

add_executable(${PROJECT_NAME} ${SOURCES} ${SSOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    inc/
)


