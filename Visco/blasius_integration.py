# Functions to be used for numerically integrating the ODE
# derived by the Boundary layer equations for flat, 
# semi-infinite plate (Blasius).
import numpy as np

def dF(f):
    """Calculate the derivaitve of the system.
    INPUT:
        f: [f1, f2, f3]
    OUTPUT:
        dF: Derivative of this system
    """
    return np.array( [f[1], f[2], -f[0]*f[2]] )
    
def RK(eta, vw, ddf0):
    """Runke-Kutta integration.
    INPUT:
        eta: Parameter values.
        vw: Suction parameter.
        ddf0: Initial value for f''.
    OUTPUT:
        F: Same as for BlasiusRK.
    """
    N = len(eta)
    F = np.zeros( (N,3) )

    #Set intial values:
    F[0,0] = -np.sqrt(2.)*vw
    F[0,1] = 0.
    F[0,2] = ddf0

    for i in range(N-1):
        #Step size:
        de = eta[i+1]-eta[i]
        
        # First step:
        l1 = de*F[i,1]
        m1 = de*F[i,2]
        n1 = -de*F[i,0]*F[i,2]

        # Second step:
        l2 = de*(F[i,1] + 0.5*m1)
        m2 = de*(F[i,2] + 0.5*n1)
        n2 = -de*(F[i,0]+0.5*l1)*(F[i,2]+0.5*n1)

        #Third step:
        l3 = de*(F[i,1]+0.5*m2)
        m3 = de*(F[i,2]+0.5*n2)
        n3 = -de*(F[i,0]+0.5*l2)*(F[i,2]+0.5*n2)

        # Fourth step:
        l4 = de*(F[i,1]+m3)
        m4 = de*(F[i,2]+n3)
        n4 = -de*(F[i,0]+l3)*(F[i,2]+n3)

        #Update values:
        F[i+1,0] = F[i,0] + (l1 + 2*l2 + 2*l3 + l4)/6.
        F[i+1,1] = F[i,1] + (m1 + 2*m2 + 2*m3 + m4)/6.
        F[i+1,2] = F[i,2] + (n1 + 2*n2 + 2*n3 + n4)/6.

    return F

def BlasiusRK(eta, vw, ddf0, fppl, fpph, tol):
    """Use Runge Kutta to integrate the system.
    INPUT:
        eta: Parameter values to integrate over.
        vw: Suction blowing parameter.
        ddf0: Guess at initial value for f''(0).
        fppl, fpph: Bounds on dff0.
        tol: Error tolerance.
    OUTPUT:
        F: len(eta) times 3 matrix with integrated values.
    """
    N = len(eta)

    anH = RK(eta,vw,fpph)
    anL = RK(eta,vw,fppl)
    finished = False #Iterations finished?

    #Check whether the correct value for f' lies in the bounds:
    dH = anH[-1,1]-1.
    dL = anL[-1,1]-1.
    if (dH*dL>0.):
        print "Correct value for f'' does not lie in the bound"
        

    #Shooting loop:
    iter = 0
    while(not finished):
        iter += 1
        fppM = 0.5*(fppl + fpph)

        anM = RK(eta,vw,fppM)
        dM = anM[-1,1]-1.

        if(dH*dM<0):
            #Value lies in the upper part:
            fppl = fppM
            dL = dM
        elif (dL*dM < 0):
            fpph = fppM
            dH = dM
        else:
            finished = True

        if np.abs(dM)<tol:
            finished = True

    # Check if solution seems unphysical:
    if (np.abs(anM[-1,2])>1e-4):
        print "Solution appears unphysical, try to increase max(eta)"

    return anM
 
