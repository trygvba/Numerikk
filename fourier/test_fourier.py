#!/usr/bin/env python3

import fourier
import numpy as np
import matplotlib.pyplot as plt

import time
# Set up some evals:
def f(x):
    return np.sin(x)

evs = f(np.linspace(0., 2*np.pi, 1000, endpoint=False))

# Fourier function:
t0 = time.time()
F = fourier.FourierFunction(evs)
t1 = time.time()
print("Time to do FourierFunction constructor (N = {0}): {1}".format(F.get_N(), t1-t0))
# Print out Fourier coefficients:
"""
for i in range(F.get_Ncoeffs()):
    print("coeff #{0}: {1}".format(i, F.get_fourier_coefficient(i)))

# Update evaluations:
F.update_evals_from_coefficients()

for i in range(F.get_N()):
    print("eval #{0}: {1}".format(i, F.get_eval(i)))
"""
