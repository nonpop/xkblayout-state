CXXFLAGS ?= -O2

PREFIX ?= /usr/local

all: xkblayout-state

XKeyboard.o: XKeyboard.cpp XKeyboard.h X11Exception.h
	$(CXX) $(CXXFLAGS) -Wall -c -o $@ $<

wrapper.o: wrapper.cpp XKeyboard.h
	$(CXX) $(CXXFLAGS) -Wall -c -o $@ $<

xkblayout-state: XKeyboard.o wrapper.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -lX11 -o xkblayout-state $^

clean:
	rm -f xkblayout-state XKeyboard.o wrapper.o

install: xkblayout-state
	install xkblayout-state $(DESTDIR)$(PREFIX)/bin

dist:
	tar cfa xkblayout-state-v1b.tar.gz Makefile README.md wrapper.cpp X11Exception.h XKeyboard.cpp XKeyboard.h

