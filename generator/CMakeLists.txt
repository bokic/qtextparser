cmake_minimum_required(VERSION 3.15)

project(generator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")

exec_program(
    "git"
    ${CMAKE_CURRENT_SOURCE_DIR}
    ARGS "describe --tags"
    OUTPUT_VARIABLE PROJECT_GIT_VERSION )

find_package(Qt5 COMPONENTS Core Xml REQUIRED)

include_directories(../include)

add_definitions( -DPROJECT_GIT_VERSION="${PROJECT_GIT_VERSION}" )

add_executable(generator
    ../src/qtextparserloader.cpp
    generator.cpp
)

target_link_libraries(generator
    Qt5::Core
    Qt5::Xml
)
