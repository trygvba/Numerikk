# Script for the numerical integration of the Blasius solution:

import numpy as np
import matplotlib.pyplot as plt

import blasius_integration as blasius

# Setting parameters:
vw = 0.7
eta = np.linspace(0.,20., 200)

fppl = 0.
fpph = 2.
tol = 1.e-12
ddf0 = 0.5

F = blasius.BlasiusRK(eta,vw, ddf0, fppl, fpph, tol)
plt.plot(eta, F[:,0], 'b')
plt.plot(eta, F[:,1], 'g')
plt.plot(eta, F[:,2], 'r')

plt.show()

####################################
#           EXERCISES:
####################################
# System parameters:
mu = 2.5e-6
U = 3.
rho = 0.578

nu = mu/rho

x = np.array( [0.25, 0.5, 1.0, 1.5] )

# Boundary layer thickness:
ind = min([i for i in range(len(eta)) if F[i,1]>=0.99])

delta = eta[ind]*np.sqrt(2*nu*x/U)
print delta


# Wall shear stress:
tau_w = mu*U*np.sqrt(U/(2*nu*x))*F[0,2]
print tau_w
