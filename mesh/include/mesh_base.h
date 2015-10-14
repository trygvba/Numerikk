//: mesh_base.h
#ifndef MESH_BASE_H
#define MESH_BASE_H

#include "triangle.h"

class MeshBase {
  public:
    // Constructors and destructors
    MeshBase();     // default constructor    
		MeshBase(struct triangulateio* in);	// constructor taking in triangulateio struct
    ~MeshBase();
    
  private:
		// Private member variables:
    int num_points; // number of points
    int num_tri;    // number of triangles
    double** points; // array with points
    int** elements;   // elements connectivity matrix

		//Private member functions:
		void create_mesh(struct triangulateio* in);	// To be used by most constructors.
};



#endif // MESH_BASE_H
