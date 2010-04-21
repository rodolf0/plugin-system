TARGET=pluginsys

CXXFLAGS=-I./include -Wall
LDFLAGS=-ldl

SOURCES = \
	main.cc \
	Plugin.cc

OBJECTS=$(SOURCES:.cc=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ 

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $^ -o $@

clean:
	rm -f *.o $(TARGET)
