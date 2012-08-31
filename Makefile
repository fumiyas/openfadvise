BUILD_TARGETS = openfadvise libopenfadvise.so

CC = cc
CFLAGS = -O2 -Wall -fPIC
LDSHARED = $(CC) -shared
LDFLAGS =

prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(exec_prefix)/lib

default: build

clean:
	rm -f $(BUILD_TARGETS)
	rm -f *.o *.so *.tmp

install:
	cp openfadvise $(bindir)
	cp libopenfadvise.so $(libdir)

build: $(BUILD_TARGETS)

openfadvise: openfadvise.sh
	sed 's#@libdir@#$(libdir)#g' openfadvise.sh >$@.tmp
	chmod +x $@.tmp
	mv $@.tmp $@

libopenfadvise.o: libopenfadvise.c

libopenfadvise.so: libopenfadvise.o
	$(LDSHARED) $(LDFLAGS) -o $@ libopenfadvise.o

