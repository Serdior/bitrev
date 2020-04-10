CC = gcc -g -no-pie
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

main: main.o bitrev.o

clean:
	rm -f main *.o *~

# vim: ts=8 sw=8 noet
