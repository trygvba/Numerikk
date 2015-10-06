#Add TriDiagMat library:
add_library(TriDiagMat tridiag.cpp)

#Add CubicSplineProblem library:
add_library(CubicSplineProblem cubicsplineproblem.cpp)

#Add Poisson1D library:
add_library(Poisson1D poisson1d.cpp)



target_link_libraries(CubicSplineProblem TriDiagMat)
target_link_libraries(Poisson1D TriDiagMat)
