PLUGINS = \
	StaticWidget

# let make search for include files in include dir
vpath %.h ../include

CXXFLAGS=-I../include -fPIC
LDFLAGS=

SOURCES=$(patsubst %,%.cc,$(PLUGINS))
LIBS=$(patsubst %,lib%.so,$(PLUGINS))

all: $(LIBS)

# include dependencies
include $(subst .cc,.d,$(SOURCES))

lib%.so: %.o
	$(CXX) -shared -Wl,-soname,lib$*.so $^ -o $@

# make the .o files depend on .d files too (dependencies)
%.d: %.cc
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$;									\
	sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;	\
	rm -f $@.$$$$

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm -f *.so *.o *.d
