CC=gcc
CFLAGS=-c -Wall -std=c99
all: hw6

hw6.o: hw6.c
	$(CC) $(CFLAGS) hw6.c

hw6: hw6.o
	$(CC) hw6.o -o a.out

clean:
	rm *.out *.o core
