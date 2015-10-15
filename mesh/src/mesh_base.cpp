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
}

MeshBase::MeshBase(struct triangulateio* in){
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
  char * options = get_triswitches(true);

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
