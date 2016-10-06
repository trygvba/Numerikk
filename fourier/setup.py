#!/usr/bin/env python3

from distutils.core import setup, Extension
from numpy import get_include
import os

# Create extension instance:
fourier_module = Extension('_fourier',
                        ['src/fourier.cpp', 'fourier.i'],
                        swig_opts = ['-c++', '-I./include'],
                        include_dirs = [get_include(), '.', './include/'],
                        libraries = ['fftw3'],
                        library_dirs= ['/usr/local/lib'])

# Setup:
os.environ['CC'] = 'g++'
setup(name="numerikk_fourier", version='0.1',
      ext_modules = [fourier_module],
      py_modules = ['fourier']
     )
