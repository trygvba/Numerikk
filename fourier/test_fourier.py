#!/usr/bin/env python3

import fourier
import numpy as np
import matplotlib.pyplot as plt

# Set up some evals:
def f(x):
    return np.sin(x)

evs = f(np.linspace(0., 2*np.pi, 20, endpoint=False))

# Fourier function:
F = fourier.FourierFunction(evs)

# Print out Fourier coefficients:
for i in range(F.get_Ncoeffs()):
    print("coeff #{0}: {1}".format(i, F.get_fourier_coefficient(i)))

# Update evaluations:
F.update_evals_from_coefficients()

for i in range(F.get_N()):
    print("eval #{0}: {1}".format(i, F.get_eval(i)))
