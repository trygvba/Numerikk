//: mesh_base.h
#ifndef MESH_BASE_H
#define MESH_BASE_H


class MeshBase {
  public:
    // Constructors and destructors
    MeshBase();     // default constructor    
    MeshBase(struct triangulateio* in);	// constructor taking in triangulateio struct
    ~MeshBase();
    
    // Public member functions
    void print();
  private:
    // Private member variables:
    int num_points; // number of points
    int num_tri;    // number of triangles
    double** points; // array with points
    int** elements;   // elements connectivity matrix

    //Private member functions:
    void create_mesh(struct triangulateio* in);	// To be used by most constructors.
    void set_points_from_triangleout(struct triangulateio *out); // To set the points
    void set_elements_from_triangleout(struct triangulateio *out); // set element data.
};



#endif // MESH_BASE_H
