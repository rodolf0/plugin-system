PLUGINS = \
	StaticWidget

# let make search for include files in include dir
vpath %.h ../include

CXXFLAGS=-I../include -fPIC
LDFLAGS=

SOURCES=$(patsubst %,%.cc,$(PLUGINS))
LIBS=$(patsubst %,lib%.so,$(PLUGINS))

all: $(LIBS)

lib%.so: %.o
	$(CXX) -shared -Wl,-soname,lib$*.so $^ -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm -f *.so *.o
