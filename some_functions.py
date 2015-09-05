import numpy as np
def make_cos_func(n):
    return lambda x: np.cos(x/np.sqrt(n)) ** n 
