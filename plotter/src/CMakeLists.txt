# Add Plotter Library
add_library(Plotter plotter.cpp)

if (VTK_LIBRARIES)
  target_link_libraries(Plotter ${VTK_LIBRARIES})  
else()
  target_link_libraries(Plotter vtkHybrid vtkWidget)
endif()
