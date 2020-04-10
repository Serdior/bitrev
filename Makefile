CC = gcc -g -no-pie
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

MAXSIZE ?= bitrev.o:256
MAXINSNS ?= bitrev.s:bitrev:48

RUN = ./run-solution --max-size $(MAXSIZE) --max-insns $(MAXINSNS) -- ./main

/usr/bin/%:
	apt-get install %

build: main /usr/bin/valgrind

main: main.o bitrev.o
	$(CC) $(LDFLAGS) -o $@ $^

test-1: build
	$(RUN) 0x0123456789ABCDEF

test-2: build
	$(RUN) 0x0102040810204080

test-3: build
	$(RUN) 0x53AC691824FEDB70

test-4: build
	$(RUN) 0xF00DCAFEC0DEBEEF

test-random: build
	$(RUN) -r 1000

test-all: test-1 test-2 test-3 test-4 test-random

clean:
	rm -f main *.o *.out *~

.PHONY: build clean test-1 test-2 test-3 test-4 test-random test-all

# vim: ts=8 sw=8 noet
