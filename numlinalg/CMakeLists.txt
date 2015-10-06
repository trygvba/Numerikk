cmake_minimum_required (VERSION 2.6)
project (NumLinAlg)


# add the binary tree to the search path for include files
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/../plotter/include")
add_subdirectory(src)
add_subdirectory(../plotter "${CMAKE_CURRENT_BINARY_DIR}/plotter")

# add the executables:
add_executable(testing tests/testing.cpp)
target_link_libraries (testing TriDiagMat)

add_executable(testspline tests/testspline.cpp)
target_link_libraries(testspline CubicSplineProblem Plotter)

add_executable(testpoisson tests/testpoisson.cpp)
target_link_libraries(testpoisson Poisson1D Plotter)
