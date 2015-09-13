CPPFLAGS = -Wall -O2
LIBS = -lgfortran -lblas -llapack -larmadillo
COMPILER = g++

dotproduct: dotproduct.cpp
	$(COMPILER) $(CPPFLAGS) dotproduct.cpp -o dotproduct $(LIBS)
