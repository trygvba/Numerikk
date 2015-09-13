CPPFLAGS = -Wall -O2
LIBS = -lgfortran -lblas -llapack -larmadillo
COMPILER = g++


all: dotproduct

dotproduct: dotproduct.cpp
	$(COMPILER) $(CPPFLAGS) dotproduct.cpp -o dotproduct $(LIBS)

clean:
	rm -f dotproduct
