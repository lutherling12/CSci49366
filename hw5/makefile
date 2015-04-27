CC=gcc
CFLAGS=-c -Wall -std=c99

all: hw5.1 hw5.2

hw5.1.o: hw5.1.c
	$(CC) $(CFLAGS) hw5.1.c

hw5.2.o: hw5.2.c
	$(CC) $(CFLAGS) hw5.2.c

hw5.1: hw5.1.o
	$(CC) hw5.1.o -o a.out

hw5.2: hw5.2.o
	$(CC) hw5.2.o -o b.out

clean:
	rm *.out *.o
