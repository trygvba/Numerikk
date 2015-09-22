CPPFLAGS = -Wall
COMPILER = g++

TARGETS = tridiag.cpp

all: testing

testing: testing.cpp
	$(COMPILER) $(CPPFLAGS) testing.cpp -o testing $(TARGETS)

clean:
	rm -f testing
