CC = g++
CFLAGS  = -g -Wall -O0
LDLIBS = -lpthread
INSTALLDIR= /usr/local/bin
INCLUDES = -I.

objects = function.o ccbenchmark.o ccbenchmark_disk.o

%.o:	%.c
	$(CC) $(CFLAGS) $(LDLIBS) -c $<


ccbenchmark:	$(objects)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(objects) $(LDLIBS)

default:	ccbenchmark

install:	ccbenchmark
	install -c -m 0555 ccbenchmark $(INSTALLDIR)

clean:
	rm -rf *.o ccbenchmark core
