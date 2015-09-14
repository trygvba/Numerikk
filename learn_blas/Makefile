INCDIR = ~/usr/include
LIBDIR = ~/usr/lib64

CPPFLAGS = -Wall -O2 -I $(INCDIR) -L $(LIBDIR) -Wl,-rpath=$(LIBDIR)
LIBS = -lgfortran -lblas -llapack -larmadillo
COMPILER = g++


all: dotproduct

dotproduct: dotproduct.cpp
	$(COMPILER) $(CPPFLAGS) dotproduct.cpp -o dotproduct $(LIBS)

matrixproduct: matrixproduct.cpp
	$(COMPILER) $(CPPFLAGS) matrixproduct.cpp -o matrixproduct $(LIBS)

clean:
	rm -f dotproduct matrixproduct
