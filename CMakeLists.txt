cmake_minimum_required(VERSION 3.15)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

project(qtextparser)

add_subdirectory(src)
add_subdirectory(generator)
add_subdirectory(benchmark)
add_subdirectory(tests)
