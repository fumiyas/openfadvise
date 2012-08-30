CFLAGS = -Wall -fPIC

prefix = /usr/local
bindir = $(prefix)/bin
libexecdir = $(prefix)/libexec

default: build

clean:
	rm -f openfadvise
	rm -f *.o *.so *.tmp

install:
	cp openfadvise $(bindir)
	cp libopenfadvise.so $(libexecdir)

build: openfadvise libopenfadvise.so

openfadvise: openfadvise.sh
	sed "s#@libexecdir@#$(libexecdir)#g" openfadvise.sh >$@.tmp
	chmod +x $@.tmp
	mv $@.tmp $@

libopenfadvise.o: libopenfadvise.c

libopenfadvise.so: libopenfadvise.o
	$(CC) -shared -o $@ libopenfadvise.o

