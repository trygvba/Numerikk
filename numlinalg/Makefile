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

_DEPS = tridiag.h cubicsplineproblem.h plotter.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tridiag.o cubicsplineproblem.o plotter.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	$(COMPILER) $(CPPFLAGS) -c -o $@ $<

#######################
#		ALL
#######################
all: testing testspline


######################
#		TRIDIAG TEST
######################
testing: $(ODIR)/testing.o $(OBJ)
	$(COMPILER) $(CPPFLAGS) -o $(TARGETDIR)/$@ $^ $(LIBS)

##############################
#		CUBICSPLINEPROBLEM TEST
##############################
testspline: $(ODIR)/testspline.o $(OBJ)
	$(COMPILER) $(CPPFLAGS) -o $(TARGETDIR)/$@ $^ $(LIBS)


.PHONY: clean
clean:
	rm -rf $(ODIR) $(TARGETDIR)/* $(INCDIR)/*~
