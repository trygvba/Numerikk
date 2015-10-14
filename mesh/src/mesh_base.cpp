//: mesh_base.cpp

#include <iostream>
#include "mesh_base.h"
#include "triangle.h"

using namespace std;


/*------------------------------------
 *      CONSTRUCTORS
 *      AND
 *      DESTRUCTORS
 *-----------------------------------*/

MeshBase::MeshBase(){
  num_points = 0;
  num_tri = 0;
  points = NULL;
  elements = NULL;
}

MeshBase::~MeshBase(){
  if(points){
    for(int i=0; i<num_points; i++){
      delete [] points[i];
    }
    delete [] points;
  }

  if(elements){
    for(int i=0; i<num_tri; i++){
      delete [] elements[i];
    }
    delete [] elements;
  }
  
}

MeshBase::MeshBase(struct triangulateio* in){
	// Before anything else, we need
	// to make sure every field of
	// the input struct is properly
	// initialized
	if (!in->pointlist){
		cout << "input pointlist not initialized." << endl;
		break;
	}
	else if(in->numberofpointattributes>0 && !in->pointattributelist){
		cout << "input point attribute list not initialized." << endl;
		break;
	}
	else if(in->numberofsegments>0 && !in->segmentlist){
		cout << "input segment list not properly set." << endl;
		break;
	}
	// pointmarkerlist or segmentmarkerlist is not set, then 
	// all markers are zero.
	else if(in->numberofholes>0 && !in->holelist ){
		cout << "input hole list not properly set." << endl;
		break;
	}
	else if(in->numberofregions>0 && !in->regionlist){
		cout << "input region list not properly set." << endl;
		break;
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


	/*-----------------
	 *  set up 
	 *  options string
	 *  and triangulate
	 *-----------------*/
	 // p: Read planar straight line graph
	 // q: quality mesh generation (Delaunay refinement)
	 // z: indexing starts at 0
	 // j: avoid duplicate points
	 // v: output voronoi struct also
	 // e: outputs list of edges
	char *options = "pqzjve";	

	/*------------------
	 *		Triangulate:
	 *------------------*/
	triangulate(options, in, out, vorout);

	/*-----------------
	 *		clean up
	 *-----------------*/
	if(out->pointlist) free(out->pointlist);
	if(out->trianglelist) free(out->trianglelist);
	if(out->segmentlist) free(out->segmentlist);
	if(out->segmentmarkerlist) free(out->segmentmarkerlist);
	if(out->edgelist) free(out->edgelist);
	if(out->edgemarkerlist) free(out->edgemarkerlist);

	delete out;

	if(vorout->pointlist) free(vorout->pointlist);
	if(vorout->pointattributelist) free(pointattributelist);
	if(vorout->edgelist) free(vorout->edgelist);
	if(vorout->normlist) free(vorout->normlist);

	delete vorout;
}
