CC=gcc
CFLAGS=-c -Wall -std=c99

all: hw3.1 hw3.2

hw3.1: hw3.1.o
	$(CC) hw3.1.o -o a.out

hw3.2: hw3.2.o
	$(CC) hw3.2.o -o b.out

hw3.1.o: hw3.1.c
	$(CC) $(CFLAGS) hw3.1.c

hw3.2.o: hw3.2.c
	$(CC) $(CFLAGS) hw3.2.c
	
clean:
	rm *.out *.o notMine sampleFile
