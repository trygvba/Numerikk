CPPFLAGS = -Wall -O2 -I ~/usr/include -L ~/usr/lib64
INCDIR = ~/usr/include
LIBDIR = ~/usr/lib64

CPPFLAGS = -Wall -O2 -I $(INCDIR) -L $(LIBDIR)
LIBS = -lgfortran -lblas -llapack -larmadillo
COMPILER = g++

dotproduct: dotproduct.cpp
	$(COMPILER) $(CPPFLAGS) dotproduct.cpp -o dotproduct $(LIBS) -Wl,-rpath,$(LIBDIR)
