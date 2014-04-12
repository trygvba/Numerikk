from numpy import *

def quadrature1D(a,b,Nq,g):
    if Nq==1:
        z = array([0.0])
        w = array([2.0])
    elif Nq==2:
        z = array([-1.0,1.0])*sqrt(1.0/3.0)
        w = array([1.0,1.0])
    elif Nq==3:
        z = array([-1.0, 0.0, 1.0])*sqrt(3.0/5.0)
        w = array([5.0, 8.0, 5.0])/9.0
    elif Nq==4:
        temp1 = 2*sqrt(6/5.0)/7.0
        temp2 = 3/7.0
        z = array([-sqrt(temp2+temp1), -sqrt(temp2-temp1), sqrt(temp2-temp1), sqrt(temp2+temp1)])
        temp1 = array([1,1,1,1])*0.5
        temp2 = array([-1, 1, 1, -1])*sqrt(30)/36.0
	w = temp1+temp2

    points = (b-a)/2.0*z+(b+a)/2.0
    return (b-a)/2.0*sum(w*g(points))
