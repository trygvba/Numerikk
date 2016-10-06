#!/usr/bin/env python3

from distutils.core import setup, Extension
from numpy import get_include
import os

# Create extension instance:
polynomial_module = Extension('_polynomial',
                        ['src/polynomial.cpp', 'polynomial.i'],
                        swig_opts = ['-c++', '-Iinclude'],
                        include_dirs = [get_include(), '.', 'include'])

# Setup:
os.environ['CC'] = 'gcc'
setup(name="numerikk_polynomial", version='0.1',
      ext_modules = [polynomial_module],
      py_modules = ['polynomial']
     )
