cmake_minimum_required(VERSION 2.8)

PROJECT(Plotter)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory (src)


