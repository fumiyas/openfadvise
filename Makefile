CFLAGS = -Wall -fPIC

default: build

clean:
	rm -f *.o *.so

build: libopenfadvise.so

libopenfadvise.o: libopenfadvise.c

libopenfadvise.so: libopenfadvise.o
	$(CC) -shared -o $@ libopenfadvise.o

