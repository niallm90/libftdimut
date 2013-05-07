test: libftdimut.o test.o
	mkdir bin
	gcc libftdimut.o test.o -lftd2xx -o bin/test

test.o: test.c libftdimut.h
	gcc $(CFLAGS) -c test.c

libftdimut.o: libftdimut.c libftdimut.h
	gcc $(CFLAGS) -c libftdimut.c

clean:
	rm -f *.o
	rm -f bin/*
