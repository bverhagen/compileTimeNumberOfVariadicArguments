CC=gcc

IDIR =../include
CFLAGS=-I$(IDIR) -isystem include/catch/include -std=c++11

ODIR=obj
OUTPUTDIR=bin
LDIR =../lib

LIBS=-lstdc++

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = catchMain.o testCountVariadicArguments.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all
all: testEleven

.PHONY: testEleven
testEleven: $(OUTPUTDIR)/testEleven

# Add C++11 flag
$(OUTPUTDIR)/testEleven: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OUTPUTDIR)/*
	rm -f $(ODIR)/*

$(shell   mkdir -p bin) 
$(shell   mkdir -p obj) 
