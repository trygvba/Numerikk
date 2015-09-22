INCDIR = ~/usr/include
LIBDIR = ~/usr/lib64

CPPFLAGS = Wall -O2 -I $(INCDIR) -L $(LIBDIR) -Wl,-rpath=$(LIBDIR)
LIBS = -lgfortran -lblas -llapack -larmadillo
COMPILER = g++

all: testing

testing: testing.cpp
	$(COMPILER) $(CPPFLAGS) testing.cpp -o testing

clean:
	rm -f testing
