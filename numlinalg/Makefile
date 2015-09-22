INCDIR = ~/usr/include
LIBDIR = ~/usr/lib64

CPPFLAGS = -Wall
LIBS = -lgfortran -lblas -llapack -larmadillo
COMPILER = g++

TARGETS = tridiag.cpp

all: testing

testing: testing.cpp tridiag.cpp
	$(COMPILER) $(CPPFLAGS) testing.cpp -o testing $(TARGETS)

clean:
	rm -f testing
