//: testtriangulatio.cpp

#include "triangle.h"
#include "mesh_base.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){
  
  double* pointlist;
  int* pointmarkerlist;
  int num_points;
  int number_of_patt;
  int bound_marks;

  num_points = 8;
  number_of_patt = 0;
  bound_marks = 1;

  // Define points
  pointlist = new double[2*num_points];
  // Outer square
  pointlist[0] = 0.;
  pointlist[1] = 0.;
  
  pointlist[2] = 0.;
  pointlist[3] = 3.;
  
  pointlist[4] = 3.;
  pointlist[5] = 0.;

  pointlist[6] = 3.;
  pointlist[7] = 3.;

  // inner square
  pointlist[8] = 1.;
  pointlist[9] = 1.;
  
  pointlist[10] = 1.;
  pointlist[11] = 2.;

  pointlist[12] = 2.;
  pointlist[13] = 1.;
  
  pointlist[14] = 2.;
  pointlist[15] = 2.;
  // Done defining points

  // pointmarkerlist:
  pointmarkerlist = new int[num_points];
  pointmarkerlist[0] = 0;
  pointmarkerlist[1] = 0;
  pointmarkerlist[2] = 0;
  pointmarkerlist[3] = 33;
  pointmarkerlist[4] = 0;
  pointmarkerlist[5] = 0;
  pointmarkerlist[6] = 0;
  pointmarkerlist[7] = 0;
  // done defining pointmarkerlist.

  // define segmentlist:
  int* segmentlist;
  int numberofsegments = 8;
  
  // define segmentlist:
  segmentlist = new int[2*numberofsegments];
  segmentlist[0] = 0;
  segmentlist[1] = 2;

  segmentlist[2] = 2;
  segmentlist[3] = 3;
  
  segmentlist[4] = 3;
  segmentlist[5] = 1;
  
  segmentlist[6] = 1;
  segmentlist[7] = 0;

  segmentlist[8] = 4;
  segmentlist[9] = 6;
  
  segmentlist[10] = 6;
  segmentlist[11] = 7;

  segmentlist[12] = 7;
  segmentlist[13] = 5;

  segmentlist[14] = 5;
  segmentlist[15] = 4;
  // done definig segmentlist

  int* segmentmarkerlist;
  segmentmarkerlist = new int[numberofsegments];

  segmentmarkerlist[0] = 0;
  segmentmarkerlist[1] = 0;
  segmentmarkerlist[2] = 0;
  segmentmarkerlist[3] = 5;
  segmentmarkerlist[4] = 0; 
  segmentmarkerlist[5] = 0;
  segmentmarkerlist[6] = 10;
  segmentmarkerlist[7] = 0;

  // Define holes:
  int num_holes = 1;
  double* holelist;

  holelist = new double[2];
  holelist[0] = 1.5;
  holelist[1] = 1.5;

  int num_regs = 0;

  
  // Declare struct!
  struct triangulateio *in = new triangulateio;
	/*
  struct triangulateio *out = new triangulateio;
  struct triangulateio *vorout = new triangulateio;
  */

  // Define the right properties of input struct
  in->pointlist = pointlist;

  in->numberofpoints = num_points;
  in->numberofpointattributes = 0;
  in->pointmarkerlist = pointmarkerlist;

  in->numberofsegments = numberofsegments;
  in->segmentlist = segmentlist;
  in->segmentmarkerlist = segmentmarkerlist;

  in->numberofholes = num_holes;
  in->holelist = holelist;
  in->numberofregions = num_regs;

  /*--------------------
   *		Let's try to
   *    triangulate
   *--------------------*/
  MeshBase testmesh(in, true);
  testmesh.print();
	
  // Clean up:
  delete [] pointlist;
  delete [] pointmarkerlist;
  delete [] segmentlist;
  delete [] segmentmarkerlist;
  delete [] holelist;
  
  delete in;
  return 0;
}
