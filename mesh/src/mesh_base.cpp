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
