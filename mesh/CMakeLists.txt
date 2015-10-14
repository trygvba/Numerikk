cmake_minimum_required (VERSION 2.6)
project (Mesh)

# add the binary tree to the search path for include files
include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)

# Add executables:
add_executable(testtriangulateio tests/testtriangulateio.cpp)
target_link_libraries(testtriangulateio 
											Triangle
											MeshBase)

