#Add TriDiagMat library:
add_library(TriDiagMat tridiag.cpp)

#Add CubicSplineProblem library:
add_library(CubicSplineProblem cubicsplineproblem.cpp)
target_link_libraries(CubicSplineProblem TriDiagMat)
