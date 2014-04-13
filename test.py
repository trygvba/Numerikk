
import meshpy.triangle as triangle
from numpy import *
from matplotlib.pyplot import *
from generate_mesh_first import *

mesh = mesh_for_intersecting_circles(2,0.5)
pts = vstack(mesh.points)
elements = vstack(mesh.elements)

triplot(pts[:,0],pts[:,1],elements[:,:3])
triangle.write_gnuplot_mesh("triangles.dat", mesh)
show()

