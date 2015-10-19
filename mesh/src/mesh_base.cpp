//: mesh_base.cpp

#include <iostream>
#include "mesh_base.h"
#include "triangle.h"
#include <cstdlib>
#include <string>
#include <stdio.h>

using namespace std;
/*------------------------------------
 *      CONSTRUCTORS
 *      AND
 *      DESTRUCTORS
 *-----------------------------------*/

MeshBase::MeshBase(){
  num_points = 0;
  num_tri = 0;
  num_edges = 0;

  points = NULL;
  elements = NULL;
  edges = NULL;
  edgemarkers = NULL;
  all_edges = false;

  shared_edge = NULL;
}

MeshBase::MeshBase(struct triangulateio* in, bool opt_edge):
all_edges(opt_edge)
{
	create_mesh(in);
}

MeshBase::~MeshBase(){
  // delete point data
  if(points){
    for(int i=0; i<num_points; i++){
      delete [] points[i];
    }
    delete [] points;
  }
  // delete element data
  if(elements){
    for(int i=0; i<num_tri; i++){
      delete [] elements[i];
    }
    delete [] elements;
  }
  
  // delete edge data

  if(edges){
    for(int i=0; i<num_edges; i++){
      delete [] edges[i];
    }
    delete [] edges;
  }

  if(edgemarkers){
    delete [] edgemarkers;
  }

  // Delete edge connectivity
  if(shared_edge){
    for(int i=0; i<num_edges; i++){
      delete [] shared_edge[i];
    }
    delete [] shared_edge;
  }
}

/*--------------------------------------------
 *		PUBLIC MEMBER FUNCTIONS
 *--------------------------------------------*/
void MeshBase::print(){
  cout << "Mesh consist of " << num_points << " points:" << endl;
  for (int i=0; i<num_points; i++){
    cout << i << ": " << points[i][0] << ", " << points[i][1] << endl;
  }

	cout << "\nMesh consists of " << num_tri << " triangles:" << endl;
	for (int i=0; i<num_tri; i++){
		cout << i << ": " << elements[i][0] << " " << elements[i][1] <<
			" " << elements[i][2] << endl;
	}

  cout << "\nMesh consists of " << num_edges;
  if(all_edges){
    cout << " edges:" << endl;
  }
  else{
    cout << " boundary edges: " << endl;
  }

  for(int i=0; i<num_edges; i++){
    cout << i << ": " << edges[i][0] << " " << edges[i][1] << endl;
  }

  if(shared_edge){
    cout << "\nThe edge connectivity is: " << endl;

    for(int i=0; i<num_edges; i++){
      cout << i << ": " << shared_edge[i][0] << " " << shared_edge[i][1] << endl;
    }
  }

}





/*-------------------------------------------
 *		PRIVATE MEMBER FUNCTIONS
 *-------------------------------------------*/

//create_mesh(...)
// to be used by various constructors.
// takes a struct triangulateio from
// Triangle and triangulates and sets
// the various member variables
// of this class correctly.
void MeshBase::create_mesh(struct triangulateio* in){
  // Before anything else, we need
  // to make sure every field of
  // the input struct is properly
  // initialized
  if (!in->pointlist){
    cout << "input pointlist not initialized." << endl;
    exit(0);
  }
  else if(in->numberofpointattributes>0 && !in->pointattributelist){
    cout << "input point attribute list not initialized." << endl;
    exit(0);
  }
  else if(in->numberofsegments>0 && !in->segmentlist){
    cout << "input segment list not properly set." << endl;
    exit(0);
  }
  // pointmarkerlist or segmentmarkerlist is not set, then 
  // all markers are zero.
  else if(in->numberofholes>0 && !in->holelist ){
    cout << "input hole list not properly set." << endl;
    exit(0);
  }
  else if(in->numberofregions>0 && !in->regionlist){
    cout << "input region list not properly set." << endl;
    exit(0);
  }

  /*-----------------------
   *	Now to set up the
   *  vorout and out
   *  struct to be used
   *  in triangle.
   *----------------------*/
  struct triangulateio *out = new triangulateio;
  struct triangulateio *vorout = new triangulateio;

  out->pointlist = NULL;
  out->trianglelist = NULL;
  out->segmentlist = NULL;
  out->segmentmarkerlist = NULL;
  out->edgelist = NULL;
  out->edgemarkerlist = NULL;
  // Voronoi
  vorout->pointlist = NULL;
  if(in->numberofpointattributes>0){
    vorout->pointattributelist = NULL;
  }
  vorout->edgelist = NULL;
  vorout->normlist = NULL;

  /*------------------
   *  get options
   *------------------*/
  char * options = get_triswitches(all_edges);

  /*------------------
   *		Triangulate:
   *------------------*/
  triangulate(options, in, out, vorout);

  /*------------------
   *	set data
   *  in object
   *------------------*/
  set_points_from_triangleout(out);
  set_elements_from_triangleout(out);
  set_edges_from_triangleout(out);

  if(all_edges){
    set_edge_connectivity(vorout);
  }
  else {
    shared_edge = NULL;  
  }
  /*-----------------
   *		clean up
   *-----------------*/
  free(out->pointlist);
  free(out->pointmarkerlist);
  free(out->trianglelist);
  free(out->segmentlist);
  free(out->segmentmarkerlist);
  free(out->edgelist);
  free(out->edgemarkerlist);

  delete out;

  free(vorout->pointlist);
  free(vorout->pointattributelist);
  free(vorout->edgelist);
  free(vorout->normlist);

  delete vorout;
  delete [] options;
}

// To set the points data from output of Triangle
void MeshBase::set_points_from_triangleout(struct triangulateio* out){
  num_points = out->numberofpoints;
  // Initialize points array
  points = new double*[num_points];
  for(int i=0; i<num_points; i++){
    points[i] = new double[2];
    points[i][0] = out->pointlist[2*i];
    points[i][1] = out->pointlist[2*i+1];
  }

}

// To set the triangle data from output of Triangle
void MeshBase::set_elements_from_triangleout(struct triangulateio* out){
  num_tri = out->numberoftriangles;
  // Initialize tri array
  elements = new int*[num_tri];

  for(int i=0; i<num_tri; i++){
    elements[i] = new int[3];
    elements[i][0] = out->trianglelist[3*i];
    elements[i][1] = out->trianglelist[3*i+1];
    elements[i][2] = out->trianglelist[3*i+2];
  }

}

// To set edge data in mesh depending on whether all edges should be given or only 
// the boundary edges.
void MeshBase::set_edges_from_triangleout(struct triangulateio *out){
  if(all_edges){
    num_edges = out->numberofedges;
    // initialize edges array
    edges = new int*[num_edges];
    edgemarkers = new int[num_edges];

    for(int i=0; i<num_edges; i++){
      edges[i] = new int[2];
      edges[i][0] = out->edgelist[2*i];
      edges[i][1] = out->edgelist[2*i+1];

      edgemarkers[i] = out->edgemarkerlist[i];
    }
  }
  else{
    num_edges = out->numberofsegments;
    // initialize edge arrays
    edges = new int*[num_edges];
    edgemarkers = new int[num_edges];

    for(int i=0; i<num_edges; i++){
      edges[i] = new int[2];
      edges[i][0] = out->segmentlist[2*i];
      edges[i][1] = out->segmentlist[2*i+1];

      edgemarkers[i] = out->segmentmarkerlist[i];
    }
    // Check orientation (I think it's not needed, when
    // all edges are in the output.
    assure_boundary_orientation();
  }

}

// Get char* poiter to be used in Triangle from options
char* MeshBase::get_triswitches(bool edges_option){
  // Initialize string to be converted and the returned

   // p: Read planar straight line graph
   // q: quality mesh generation (Delaunay refinement)
   // z: indexing starts at 0
   // j: avoid duplicate points
   // v: output voronoi struct also
   // e: outputs list of edges
  string options = "pqzjv";

  if(edges_option){
    options += "e";
  }


  // Convert string to char*
  char* res = new char[options.length()+1];
  copy(options.begin(), options.end(), res);
  res[options.length()] = '\0';
  return res;

}

/*---------------------------------
 * Functions to switch orientation
 * on boundary edges
 * so that subsequent natural
 * boundary conditions are
 * treated appropriately.
 *----------------------------------*/
int MeshBase::get_element_from_edge(int edge_ind){
  // go through each element
  for(int i=0; i<num_tri; i++){
    // check if first edge index is in element
    int tmp1 = edges[edge_ind][0];
    if( tmp1==elements[i][0] || tmp1==elements[i][1] || tmp1==elements[i][2]){
      // Check if also second index is in element
      int tmp2 = edges[edge_ind][1];
      if(tmp2==elements[i][0] || tmp2==elements[i][1] || tmp2==elements[i][2]){
        return i;
      }
    }
  }
  cout << "Couldn't find edge in any element" << endl;
  return -1;
}

int MeshBase::get_point_not_on_edge(int el_ind, int edge_ind){
  // go through each point in the element:
  for(int indp=0; indp<3; indp++){
    int tmp=elements[el_ind][indp];
    // Check if point is not on edge
    if(tmp!=edges[edge_ind][0] && tmp!=edges[edge_ind][1] ){
      return tmp;
    }
  }
  cout << "Could not find point outside of edge on element." << endl;
  return -1;
}

// Function to check if boundary edge is properly oriented:
bool MeshBase::properly_oriented(int edge_ind){
  // First of all check if edge is on the boundary:
  if(edgemarkers[edge_ind] == 0){
    cout << "Edge is not on boundary. Properly oriented by default" << endl;
    return true;
  }
  // get vector for edge:
  double xe = points[edges[edge_ind][1]][0]-points[edges[edge_ind][0]][0];
  double ye = points[edges[edge_ind][1]][1]-points[edges[edge_ind][0]][1];

  // Get vector starting from the same point as edge and ending at the point
  // in element, not on edge.
  int el_ind = get_element_from_edge(edge_ind);
  int p_ind = get_point_not_on_edge(el_ind, edge_ind);

  double xt = points[p_ind][0] - points[edges[edge_ind][0]][0];
  double yt = points[p_ind][1] - points[edges[edge_ind][0]][1];

  // And return true if cross product is positive:
  return (xe*yt-xt*ye>0);
}

//Function to swap orientation of edge if not correct.
void MeshBase::swap_orientation(int edge_ind){
  int tmp = edges[edge_ind][0];
  edges[edge_ind][0] = edges[edge_ind][1];
  edges[edge_ind][1] = tmp;
}

// Lastly we go through boundary edges and assure orientation:
void MeshBase::assure_boundary_orientation(){
  // Go through all edges:
  for(int inde=0; inde<num_edges; inde++){
    //Check if on boundary:
    if(edgemarkers[inde]!=0){
      //Check if properly oriented:
      if(!properly_oriented(inde)){
        //if not, swap indices
        swap_orientation(inde);
      }
    }
  }
}

// Function to get array that gives which triangles share an edge:
void MeshBase::set_edge_connectivity(struct triangulateio *vorout){
  //Initialize array:
  shared_edge = new int*[num_edges];
  
  for(int i=0; i<num_edges; i++){
    shared_edge[i] = new int[2];
    shared_edge[i][0] = vorout->edgelist[2*i];
    shared_edge[i][1] = vorout->edgelist[2*i+1];
  }
}
