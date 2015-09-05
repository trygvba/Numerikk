import numpy as np
import matplotlib.pyplot as pyp
import some_functions as cosn

n = 1000000
x = np.linspace(-5,5,1000)
f = cosn.make_cos_func(n)
y1 = f(x)
y2 = np.exp(-0.5*x**2)
pyp.plot(x,y1,'b')
pyp.plot(x,y2,'r')
pyp.show()
