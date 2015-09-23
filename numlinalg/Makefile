CPPFLAGS = -Wall
COMPILER = g++

DEPS = tridiag.h
OBJ = testing.o tridiag.o

%.o: %.cpp $(DEPS)
	$(COMPILER) $(CPPFLAGS) -c -o $@ $<

testing:  $(OBJ)
	$(COMPILER) $(CPPFLAGS) -o $@ $^
clean:
	rm -f testing *.o *~
