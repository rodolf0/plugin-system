CXXFLAGS=-I../include -fPIC
LDFLAGS=

PLUGINS = \
	StaticWidget

LIBS=$(patsubst %,lib%.so,$(PLUGINS))

all: $(LIBS)

lib%.so: %.o
	$(CXX) -shared -Wl,-soname,$@ $^ -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@


clean:
	rm -f *.so *.o
