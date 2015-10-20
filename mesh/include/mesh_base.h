//: mesh_base.h
#ifndef MESH_BASE_H
#define MESH_BASE_H


class MeshBase {
  public:
    // Constructors and destructors
    MeshBase();     // default constructor    
    MeshBase(struct triangulateio* in, bool opt_edge=false);	// constructor taking in triangulateio struct
    ~MeshBase();
    
    //Public member variables
    double** points;  // array with points
    int** elements;   // elements connectivity matrix
    // A note on the edges:
    /*------------------------------------------
     * If mesh is created with all edges
     * list of edges contains all edges,
     * and boundary edges are those with
     * non-zero edgemarker.
     * Otherwise, list of edges is just
     * boundary edges. Checking for
     * orientation on boundary edges
     * should still be done.
     *-------------------------------------------*/
    bool all_edges;   // all edges are in mesh, or only boundary edges.
    int** edges;      // list of edges 
    int* edgemarkers; // list of edge markers

    int** shared_edge;// array of triangles sharing an edge

    // Public member functions
    void print();
    int get_number_of_points();
    int get_number_of_triangles();
    int get_number_of_edges();
    
  private:
    // Private member variables:
    int num_points; // number of points
    int num_tri;    // number of triangles
    int num_edges;   // number of edges

    //Private member functions:
    void create_mesh(struct triangulateio* in);	// To be used by most constructors.
    void set_points_from_triangleout(struct triangulateio *out); // To set the points
    void set_elements_from_triangleout(struct triangulateio *out); // set element data.
    void set_edges_from_triangleout(struct triangulateio *out);    // set edge data.
    char* get_triswitches(bool edges_option);                 // Get char* pointer to be used by Triangle.
    // To be used when checking orientation of edge
    int get_element_from_edge(int edge_ind);                  // Get element index from edge index
    int get_point_not_on_edge(int el_ind, int edge_ind);  // get point index in element, not on edge.
    bool properly_oriented(int edge_ind);   // Checks if boundary edge is properly oriented.
    void swap_orientation(int edge_ind);
    void assure_boundary_orientation();     // Assure edge orientation at the boundary.

    //Get edge_connectivity
    void set_edge_connectivity(struct triangulateio *vorout);   // To get triangles sharing an edgelre
};



#endif // MESH_BASE_H
