TARGET=wbar

SOURCES = \
	main.cc \
	Plugin.cc

# let make search for include files in include dir
vpath %.h include

CXXFLAGS=-I../include -Wall
LDFLAGS=-ldl

OBJECTS=$(SOURCES:.cc=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ 

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $^

clean:
	rm -f *.o $(TARGET)
