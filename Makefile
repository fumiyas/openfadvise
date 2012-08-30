CFLAGS = -Wall -fPIC

prefix = /usr/local
bindir = $(prefix)/bin
libdir = $(prefix)/lib

default: build

clean:
	rm -f openfadvise
	rm -f *.o *.so *.tmp

install:
	cp openfadvise $(bindir)
	cp libopenfadvise.so $(libdir)

build: openfadvise libopenfadvise.so

openfadvise: openfadvise.sh
	sed "s#@libdir@#$(libdir)#g" openfadvise.sh >$@.tmp
	chmod +x $@.tmp
	mv $@.tmp $@

libopenfadvise.o: libopenfadvise.c

libopenfadvise.so: libopenfadvise.o
	$(CC) -shared -o $@ libopenfadvise.o

