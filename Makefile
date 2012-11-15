BUILD_TARGETS = openfadvise openfadvise.so

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
	cp openfadvise.so $(libdir)

build: $(BUILD_TARGETS)

openfadvise: openfadvise.sh
	sed 's#@libdir@#$(libdir)#g' openfadvise.sh >$@.tmp
	chmod +x $@.tmp
	mv $@.tmp $@

openfadvise.o: openfadvise.c

openfadvise.so: openfadvise.o
	$(LDSHARED) $(LDFLAGS) -o $@ openfadvise.o

