cmake_minimum_required(VERSION 3.15)

project(qtextparser LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")

find_package(Qt5 COMPONENTS Core REQUIRED)

include_directories(../include)

add_library(qtextparser SHARED
    qtextparser.cpp
)

target_link_libraries(qtextparser
    Qt5::Core
)

set_target_properties(qtextparser PROPERTIES
    VERSION "0.9"
    SOVERSION "0"
)
