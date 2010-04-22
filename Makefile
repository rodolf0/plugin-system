TARGET=pluginsys

SOURCES = \
	main.cc \
	Plugin.cc

# let make search for include files in include dir
vpath %.h include

CXXFLAGS=-I./include -Wall
LDFLAGS=-ldl

OBJECTS=$(SOURCES:.cc=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ 

# include dependencies
include $(subst .cc,.d,$(SOURCES))

# make the .o files depend on .d files too (dependencies)
%.d: %.cc
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$;									\
	sed 's,\($*\).o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;	\
	rm -f $@.$$$$

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $^

clean:
	rm -f *.o *.d $(TARGET)
