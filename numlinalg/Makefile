IDIR =include
CPPFLAGS = -Wall -I $(IDIR)
COMPILER = g++

ODIR=build
SRCDIR=src
TESTDIR=tests
LDIR=lib
TARGETDIR=bin

VPATH = $(SRCDIR):$(TESTDIR)

LIBS= -lm

_DEPS = tridiag.h cubicsplineproblem.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tridiag.o testing.o testspline.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	$(COMPILER) $(CPPFLAGS) -c -o $@ $<

testing: $(OBJ)
	$(COMPILER) $(CPPFLAGS) -o $(TARGETDIR)/$@ $^ $(LIBS)

testspline: $(OBJ)
	$(COMPILER) $(CPPFLAGS) -o $(TARGETDIR)/$@ $^ $(LIBS)


.PHONY: clean
clean:
	rm -rf $(ODIR) $(TARGETDIR)/* $(INCDIR)/*~
