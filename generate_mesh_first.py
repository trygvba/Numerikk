import meshpy.triangle as triangle
from numpy import *

def CircleSegments(middle,radius,num_points,a_min=0.,a_max=2.*pi,edge_length=-1,**options):
  # check for closed loop
  number_points=num_points
  if edge_length>0:
    number_points=floor(abs(radius/edge_length*(a_max-a_min)))+1
    
  delta=(a_max-a_min)/number_points
  closed=False;
  if abs(a_max-a_min-2*pi)<0.1*delta:
    closed=True
  
  t=linspace(a_min,a_max,number_points,not closed)
  # define points
  points=[(middle[0]+radius*cos(angle),middle[1]+radius*sin(angle)) for angle in t]
  
  if options.get("sliced"):
    points = [point for point in points if options.get("condition")(point)]
  # define vertices
  vertices=[(j,j+1) for j in range(0,len(points)-1,1)]
  if closed==True:
    vertices+=[(len(points)-1,0)]
  return points,vertices;

def offset_list(vertices,offset):
    result = [];
    for i in vertices:
        result.append((i[0]+offset,i[1]+offset))
    return result


def round_trip_connect(start, end):
    result = []
    for i in range(start, end):
        result.append((i, i+1))
        result.append((end, start))
    return result
#--------------------------------------------------------------------------
#	MAIN FUNCTION TO BE USED HERE:
#--------------------------------------------------------------------------
def mesh_for_intersecting_circles(radius,volume_tolerance):
  char_length = sqrt(2*volume_tolerance)
  circumference = 2*pi*radius
  num_points = floor(circumference/char_length)
  center1 = [-radius,0]
  radius1 = 1.1*radius
  points1, vertices1 = CircleSegments(center1,radius1,num_points,a_min=0.,a_max=2.0*pi,edge_length=-1,sliced=True,\
condition = lambda point: point[0]<0)

  center2 = [radius,0]
  radius2 = 1.1*radius
  points2, vertices2 = CircleSegments(center2,radius2,num_points,a_min=-pi,a_max=pi,edge_length=-1,sliced=True,\
condition = lambda point: point[0]>0)

  del vertices1[-1]
  del vertices2[-1]
  n = len(points1)
  points = points1 + points2
  vertices = vertices1+offset_list(vertices2,n)
  #Connect last from segment 1 to first from segment 2:
  vertices.append((n-1,n))
  #Connect last from segment 2 to first from segment 1:
  vertices.append((len(points)-1,0)) 

  info = triangle.MeshInfo()
  info.set_points(points)
  info.set_facets(vertices)
	
  mesh = triangle.build(info, max_volume=volume_tolerance)
  print "Mesh generation done"
  print "Number of nodes: %d" %len(mesh.points)
  print "Number of elements: %d" %len(mesh.elements) 
  return mesh