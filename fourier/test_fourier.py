#!/usr/bin/env python3

import fourier
import numpy as np
import matplotlib.pyplot as plt

import time
# Set up some evals:
def f(x):
    return 1.*(x < np.pi )

N = 1000
x = np.linspace(0., 2*np.pi, N, endpoint = False)
evs = f(x)

# Fourier function:
t0 = time.time()
F = fourier.FourierFunction(evs)
t1 = time.time()
print("Time to do FourierFunction constructor (N = {0}): {1}".format(F.get_N(), t1-t0))

# Next we use smoothing:
num_smoothings = 3
for i in range(num_smoothings):
    fourier.fejer_smoothing(F)
F.update_evals_from_coefficients()

# Plot function:
plt.plot(x,F.get_evals())
plt.show()

