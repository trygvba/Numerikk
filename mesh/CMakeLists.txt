cmake_minimum_required (VERSION 2.6)
project (Mesh)

# add the binary tree to the search path for include files
include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)
