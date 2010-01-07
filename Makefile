all: xkblayout-state

XKeyboard.o: XKeyboard.cpp XKeyboard.h X11Exception.h
	g++ -c -Wall -O2 XKeyboard.cpp -o XKeyboard.o

wrapper.o: wrapper.cpp XKeyboard.h
	g++ -c -Wall -O2 wrapper.cpp -o wrapper.o

xkblayout-state: XKeyboard.o wrapper.o
	g++ XKeyboard.o wrapper.o -lX11 -o xkblayout-state

clean: 
	rm -f xkblayout-state XKeyboard.o wrapper.o

dist:
	tar cfa xkblayout-state-v1b.tar.gz Makefile README.md wrapper.cpp X11Exception.h XKeyboard.cpp XKeyboard.h

