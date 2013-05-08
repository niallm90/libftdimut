CC=gcc
CFLAGS=-Wall -pedantic

all: libftdimut.so

libftdimut.so: libftdimut.so.o
	gcc -shared -Wl,-soname,libftdimut.s0.1 -lftd2xx libftdimut.so.o -o bin/libftdimut.so.1.0

libftdimut.so.o: libftdimut.c libftdimut.h
	$(CC) $(CFLAGS) -fPIC -c libftdimut.c -o libftdimut.so.o

clean:
	rm -f *.o *.so bin/* libftdimut.so*

install:
	cp bin/libftdimut.so.1.0 /usr/lib/
	cp libftdimut.h /usr/include/
	ln -sf /usr/lib/libftdimut.so.1.0 /usr/lib/libftdimut.so.1
	ln -sf /usr/lib/libftdimut.so.1 /usr/lib/libftdimut.so
	ldconfig
