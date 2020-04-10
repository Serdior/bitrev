CC = gcc -g -no-pie
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

main: main.o bitrev.o

test-1: main
	./main 0x0123456789ABCDEF

test-2: main
	./main 0x0102040810204080

test-3: main
	./main 0x53AC691824FEDB70

test-4: main
	./main 0xF00DCAFEC0DEBEEF

test-random: main
	./main -r 1000

clean:
	rm -f main *.o *~

.PHONY: clean test-1 test-2 test-3 test-4 random-test

# vim: ts=8 sw=8 noet
