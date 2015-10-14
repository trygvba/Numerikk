# Add Triangle library
set_source_files_properties( triangle.c PROPERTIES LANGUAGE CXX)
add_library(Triangle triangle.c)

add_library(MeshBase mesh_base.cpp)
target_link_libraries(MeshBase Triangle)
