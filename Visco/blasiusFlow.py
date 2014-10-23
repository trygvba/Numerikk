# Script to show the flow over a flat plate:

import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import blasius_integration as blasius
###################################

vw = 0.
ddf0 = 0.46
fppl = 0.
fpph = 1.
tol = 1e-8

# Setting up grid
x = np.linspace(0.1, 1., 10) 
y = np.linspace(0., 1., 11)

eta = np.linspace(0., 6., 100)
F = blasius.BlasiusRK(eta, vw, ddf0, fppl, fpph, tol)
F_intp = interp1d(eta,F[:,0])
Fp_intp = interp1d(eta,F[:,1])

X, Y = np.meshgrid(x,y, indexing='ij')
psi = np.zeros( (len(x), len(y)) )
u = np.zeros( (len(x), len(y) ) )
v = np.zeros( (len(x), len(y) ) )
for i in range(len(x)):
    eta_x = y*np.sqrt(1/(2*x[i]))
    F_x = F_intp(eta_x)
    Fp_x = Fp_intp(eta_x)
    psi[i,:] = np.sqrt(2*x[i])*F_x
    u[i,:] = Fp_x
    v[i,:] = np.sqrt(1/(2.*x[i]))*(eta_x*Fp_x - F_x)

plt.figure()
CS = plt.contour(X,Y, psi, 20)
Q = plt.quiver(X, Y, u, v)
plt.show()
