CXXFLAGS ?= -O2

PREFIX ?= /usr/local

headers := XKeyboard.h X11Exception.h
sources := XKeyboard.cpp wrapper.cpp
objects := $(sources:.cpp=.o)
program := xkblayout-state

all: $(program)

$(objects): %.o: %.cpp $(headers)
	$(CXX) $(CXXFLAGS) -Wall -c -o $@ $<

$(program): $(objects)
	$(CXX) $(CXXFLAGS) -lX11 $(LDFLAGS) -o $@ $^

clean:
	rm -f $(program) $(objects)

install: $(program)
	install $(program) $(DESTDIR)$(PREFIX)/bin

dist:
	tar cfa $(program)-v1b.tar.gz Makefile README.md $(headers) $(sources)

