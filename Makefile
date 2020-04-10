CC = gcc -g -no-pie
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

# "insts": 48

build: main
	./check-solution --max-size 256 bitrev.o

main: main.o bitrev.o
	$(CC) $(LDFLAGS) -o $@ $^

test-1: build
	./main 0x0123456789ABCDEF

test-2: build
	./main 0x0102040810204080

test-3: build
	./main 0x53AC691824FEDB70

test-4: build
	./main 0xF00DCAFEC0DEBEEF

test-random: build
	./main -r 1000

clean:
	rm -f main *.o *~

.PHONY: build clean test-1 test-2 test-3 test-4 random-test

# vim: ts=8 sw=8 noet
